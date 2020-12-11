#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Editor.h"
#include "GlobalWordList.h"

void Editor::loadTextFile(string path) {
	try {
		textFile_ = new TextFile(path);
		vector<string> wordList_(textFile_->createWordList(DELIMITER_WORD));
		GlobalWordList::getInstance()->setWordList(wordList_);

		textFile_->setPageList(wordList_);
	}
	catch (string& errorMsg) {
		state = STATE_ERROR;
		errorType = ERROR_FILE_NOT_FOUND;
		throw;
	}
	
}

int Editor::loadCommand(string command) {
	string param;

	params_.clear();
	try {
		commandType_ = command[0];
		if (commandType_ == COMMAND_NEXT_PAGE || commandType_ == COMMAND_PRE_PAGE || commandType_ == COMMAND_SAVE_FILE)
			return STATE_NORMAL;

		string paramsText(command.substr(1, command.size() - 1));
		paramsText = paramsText.substr(1, paramsText.size() - 2);
		stringstream strStream(paramsText);

		while (getline(strStream, param, DELIMITER_PARAMETER)) {
			params_.push_back(param);
		}

	}catch (exception& e) {
		return STATE_ERROR;
	}
	return STATE_NORMAL;
}
int Editor::checkLineNum(string paramLineNum) {
	int lineNum = atoi(paramLineNum.c_str());

	if (lineNum < 1)
		return STATE_ERROR;
	return STATE_NORMAL;
}
int Editor::checkWordNum(string paramsWordNum) {
	int wordNum = atoi(paramsWordNum.c_str());

	if (wordNum > MAX_LINE_SIZE || wordNum < 1)
		return STATE_ERROR;
	return STATE_NORMAL;
}
int Editor::checkWord(string word) {
	if (word.size() > MAX_LINE_NUM || word.size() == 0 || word == " ")
		return STATE_ERROR;
	return STATE_NORMAL;
}

int Editor::checkCommandValid(char commandType, vector<string> params) {

	errorType = NOT_ERROR;
	switch (commandType) {
	case COMMAND_INSERT_WORD:
		if (params.size() != 3) {
			
			return STATE_ERROR;
		}
		return checkLineNum(params[0]) * checkWordNum(params[1]) * checkWord(params[2]);

	case COMMAND_DELETE_WORD:
		if (params.size() != 2) {
			errorType = ERROR_PARAMETER_NUM;
			return STATE_ERROR;
		}
		return checkLineNum(params[0]) * checkWordNum(params[1]);

	case COMMAND_RESTRUCT_PAGE:
		if (params.size() != 1) {
			errorType = ERROR_PARAMETER_NUM;
			return STATE_ERROR;
		}
		return checkWord(params[0]);

	case COMMAND_MODIFY_WORD:
		if (params.size() != 2) {
			errorType = ERROR_PARAMETER_NUM;
			return STATE_ERROR;
		}
		return checkWord(params[0]) * checkWord(params[1]);

	case COMMAND_PRE_PAGE:
		if (currentPage == 0) {
			errorType = ERROR_OUT_OF_PAGE;
			return STATE_ERROR;
		}
		return STATE_NORMAL;

	case COMMAND_NEXT_PAGE:
		if (currentPage == textFile_->getPageList().size() - 1) {
			errorType = ERROR_OUT_OF_PAGE;
			return STATE_ERROR;
		}
		return STATE_NORMAL;

	case COMMAND_SAVE_FILE:
		return STATE_NORMAL;

	default:
		errorType = ERROR_COMMAND_TYPE;
		return STATE_ERROR;
	}
}

void Editor::handlingCommand(string command) {

	state |= loadCommand(command);
	state |= checkCommandValid(commandType_, params_);

	if (state == STATE_ERROR) {
		errorType = errorType == NOT_ERROR ? ERROR_PARAMETER_VAL : errorType;
		return;
	}
	switch (commandType_) {
	case COMMAND_INSERT_WORD:
		state = insertWord(params_);
		break;
	case COMMAND_DELETE_WORD:
		state = delWord(params_);
		break;
	case COMMAND_RESTRUCT_PAGE:
		state = restructByWord(params_);
		break;
	case COMMAND_MODIFY_WORD:
		state = modifyAllWord(params_);
		break;
	case COMMAND_PRE_PAGE:
		--currentPage;
		break;
	case COMMAND_NEXT_PAGE:
		++currentPage;
		break;
	case COMMAND_SAVE_FILE:
		saveFile();
		break;
	}
}

int Editor::insertWord(vector<string> params) {
	int lineNum = atoi(params[0].c_str());
	int wordNum = atoi(params[1].c_str());
	int idx = GlobalWordList::getInstance()->getIndex(lineNum, wordNum);

	if (idx < 0) {
		errorType = ERROR_OUT_OF_INDEX;
		return STATE_ERROR;
	}
	GlobalWordList::getInstance()->insertWord(idx, params[2]);
	textFile_->setPageList(GlobalWordList::getInstance()->getWordList());
	
	return STATE_NORMAL;
}

int Editor::delWord(vector<string> params) {
	int lineNum = atoi(params[0].c_str());
	int wordNum = atoi(params[1].c_str());
	int idx = GlobalWordList::getInstance()->getIndex(lineNum, wordNum);

	if (idx < 0) {
		errorType = ERROR_OUT_OF_INDEX;
		return STATE_ERROR;
	}
	GlobalWordList::getInstance()->delWord(idx);
	textFile_->setPageList(GlobalWordList::getInstance()->getWordList());

	return STATE_NORMAL;
}

int Editor::modifyAllWord(vector<string> params) {
	GlobalWordList::getInstance()->modifyAllWord(params[0], params[1]);
	textFile_->setPageList(GlobalWordList::getInstance()->getWordList());
	return STATE_NORMAL;
}

int Editor::restructByWord(vector<string> params) {
	int idx = GlobalWordList::getInstance()->getIndex(params[0]);
	if (idx < 0) {
		errorType = ERROR_NOT_FOUND_WORD;
		return STATE_ERROR;
	}
	currentPage = textFile_->restructPageList(GlobalWordList::getInstance()->getWordList(), idx);

	return STATE_NORMAL;
}

void Editor::saveFile() {
	textFile_->saveTextFile(GlobalWordList::getInstance()->getWordList());
	state = STATE_TERMINATE;
}

void Editor::printPage() {
	int lineBeginIdx = getBeginLineNum(currentPage) + 1;
	vector<string> page = textFile_->getPageList().at(currentPage);
	int lineNumInPage = page.size();

	for(int lineIter = 0; lineIter < page.size(); lineIter++) {
		cout << setw(2) << lineBeginIdx + lineIter << "|\t" << page[lineIter] << endl;
	}
	cout << CUTOFF_LINE << endl << COMMAND_HELP_MESSAGE << endl << CUTOFF_LINE << endl;

}
int Editor::getBeginLineNum(int pageNo) {
	int lineNum = 0;
	
	for (int pageIdx = 0; pageIdx < pageNo; pageIdx++) {
		lineNum += textFile_->getPageList().at(pageIdx).size();
	}
	return lineNum;
}

void Editor::printError() {
	switch (errorType) {
	case ERROR_FILE_NOT_FOUND:
		cout << ERR_MSG_FILE_NOT_FOUND << ERR_MSG_TERMINATE;
		break;
	case ERROR_COMMAND_TYPE :
		cout << ERR_MSG_COMMAND_TYPE << ERR_MSG_RE_INPUT;
		break;
	case ERROR_PARAMETER_VAL:
		cout << ERR_MSG_PARAMETER_VAL << ERR_MSG_RE_INPUT;
		break;
	case ERROR_PARAMETER_NUM:
		cout << ERR_MSG_PARAMETER_NUM << ERR_MSG_RE_INPUT;
		break;
	case ERROR_OUT_OF_INDEX:
		cout << ERR_MSG_OUT_OF_INDEX << ERR_MSG_RE_INPUT;
		break;
	case ERROR_OUT_OF_PAGE:
		cout << ERR_MSG_OUT_OF_PAGE;
		break;
	case ERROR_NOT_FOUND_WORD:
		cout << ERR_MSG_NOT_FOUND_WORD << ERR_MSG_RE_INPUT;
		break;
	default:
		cout << ERR_MSG_RE_INPUT;
	}
	cout << CUTOFF_LINE << endl;

	state = STATE_NORMAL;
}
