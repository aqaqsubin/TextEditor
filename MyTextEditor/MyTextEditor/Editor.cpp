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
		if (textFile_->isLastPage(currentPage)) {
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
		printError();
		printPage();
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
		state = restructByWord(params_[0]);
		break;
	case COMMAND_MODIFY_WORD:
		state = modifyAllWord(params_);
		break;
	case COMMAND_PRE_PAGE:
		printPrePage();
		break;
	case COMMAND_NEXT_PAGE:
		printNextPage();
		break;
	case COMMAND_SAVE_FILE:
		saveFile();
		break;
	}

	printError();
	if (commandType_ != COMMAND_NEXT_PAGE && commandType_ != COMMAND_PRE_PAGE)
		printPage();

}

int Editor::insertWord(vector<string> params) {
	int lineNum = atoi(params[0].c_str());
	int wordNum = atoi(params[1].c_str());
	int idx = GlobalWordList::getInstance()->getIndex(lineNum, wordNum);

	if (idx < 0) {
		errorType = ERROR_OUT_OF_INDEX;
		return STATE_ERROR;
	}
	GlobalWordList::getInstance()->insertWord(idx+1, params[2]);
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

int Editor::restructByWord(string param) {
	int idx = GlobalWordList::getInstance()->getIndex(param);
	if (idx < 0) {
		errorType = ERROR_NOT_FOUND_WORD;
		return STATE_ERROR;
	}
	currentPage = textFile_->restructPageList(GlobalWordList::getInstance()->getWordList(), idx);

	return STATE_NORMAL;
}
int Editor::restorePageList() {
	textFile_->restructPageList(GlobalWordList::getInstance()->getWordList(), 0);
	return STATE_NORMAL;
}
void Editor::saveFile() {
	textFile_->saveTextFile(GlobalWordList::getInstance()->getWordList());
	state = STATE_TERMINATE;
}
void Editor::printPrePage() {
	restorePageList();
	vector<string> resultPage;
	vector<string> curPage = textFile_->getPageList().at(currentPage);
	vector<string> prePage = textFile_->getPageList().at(currentPage - 1);
	int lineBeginIdx = getBeginLineNum(currentPage - 1) + 1;
	int prePageSize = textFile_->getPageSize(currentPage - 1);

	for (int preIdx = 0; preIdx < prePageSize; preIdx++) {
		resultPage.push_back(prePage[preIdx]);
	}
	if (currentPage - 1 == 0 && prePageSize < MAX_LINE_NUM) {
		for (int curIdx = 0; curIdx < curPage.size()- prePageSize; curIdx++) {
			resultPage.push_back(curPage[curIdx]);
		}
	}

	for (int lineIter = 0; lineIter < resultPage.size(); lineIter++) {
		cout << setw(2) << lineBeginIdx + lineIter << "|\t" << resultPage[lineIter] << endl;
	}
	cout << CUTOFF_LINE << endl << COMMAND_HELP_MESSAGE << endl << CUTOFF_LINE << endl;
	currentPage--;
}
void Editor::printPage() {
	vector<string> page = textFile_->getPageList().at(currentPage);
	int lineBeginIdx = getBeginLineNum(currentPage) + 1;
	int pageSize = textFile_->getPageSize(currentPage);
	
	for(int lineIter = 0; lineIter < pageSize; lineIter++) {
		cout << setw(2) << lineBeginIdx + lineIter << "|\t" << page[lineIter] << endl;
	}
	cout << CUTOFF_LINE << endl << COMMAND_HELP_MESSAGE << endl << CUTOFF_LINE << endl;
}
void Editor::printNextPage() {
	vector<string> resultPage;
	vector<string> curPage = textFile_->getPageList().at(currentPage);
	vector<string> nextPage = textFile_->getPageList().at(currentPage + 1);
	int lineBeginIdx = getBeginLineNum(currentPage + 1) + 1;
	int nextPageSize = textFile_->getPageSize(currentPage + 1);

	if (textFile_->isLastPage(currentPage + 1) && nextPageSize < MAX_LINE_NUM) {

		lineBeginIdx = getBeginLineNum(currentPage + 1) - (MAX_LINE_NUM - nextPageSize);
		for (int curIdx = nextPageSize - 1; curIdx < curPage.size(); curIdx++) {
			resultPage.push_back(curPage[curIdx]);
		}
	}
	for (int curIdx = 0; curIdx < nextPage.size(); curIdx++) {
		resultPage.push_back(nextPage[curIdx]);
	}

	for (int lineIter = 0; lineIter < resultPage.size(); lineIter++) {
		cout << setw(2) << lineBeginIdx + lineIter << "|\t" << resultPage[lineIter] << endl;
	}
	cout << CUTOFF_LINE << endl << COMMAND_HELP_MESSAGE << endl << CUTOFF_LINE << endl;
	currentPage++;
}
int Editor::getBeginLineNum(int pageNo) {
	int lineNum = 0;
	
	for (int pageIdx = 0; pageIdx < pageNo; pageIdx++) {
		lineNum += textFile_->getPageSize(pageIdx);
	}
	return lineNum;
}

void Editor::printError() {
	if (state == STATE_NORMAL || state == STATE_TERMINATE)
		return;
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
