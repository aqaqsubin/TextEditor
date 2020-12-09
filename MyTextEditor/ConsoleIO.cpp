#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "ConsoleIO.h"
#include "GlobalWordList.h"

void ConsoleIO::loadTextFile(string path) {
	textFile_ = new TextFile(path);
	vector<string> wordList = textFile_->createWordList(DELIMITER_WORD);
	GlobalWordList::getInstance()->setWordList(wordList);
	
	textFile_->setPageList(wordList);
}

vector<string>& ConsoleIO::splitParameters(string paramsText) {
	stringstream strStream(paramsText);
	vector<string> params;
	string param;

	while (getline(strStream, param, DELIMITER_PARAMETER)) {
		params.push_back(param);
	}
	return params;
}
int ConsoleIO::checkLineNum(string paramLineNum) {
	int lineNum = atoi(paramLineNum.c_str());

	if (lineNum > MAX_LINE_NUM || lineNum < 1)
		return STATE_ERROR;
	return STATE_NORMAL;
}
int ConsoleIO::checkWordNum(string paramsWordNum) {
	int wordNum = atoi(paramsWordNum.c_str());

	if (wordNum > MAX_LINE_SIZE || wordNum < 1)
		return STATE_ERROR;
	return STATE_NORMAL;
}
int ConsoleIO::checkWord(string word) {
	if (word.size() > MAX_LINE_NUM || word.size() == 0 || word == " ")
		return STATE_ERROR;
	return STATE_NORMAL;
}
int ConsoleIO::checkUserInput(char commandType, vector<string> params) {

	switch (commandType) {
	case COMMAND_INSERT_WORD:
		if (params.size() != 3)
			return STATE_ERROR;

		return checkLineNum(params[0]) * checkWordNum(params[1]) * checkWord(params[2]);

	case COMMAND_DELETE_WORD:
		if (params.size() != 2)
			return STATE_ERROR;

		return checkLineNum(params[0]) * checkWordNum(params[1]);

	case COMMAND_RESTRUCT_PAGE:
		if (params.size() != 1)
			return STATE_ERROR;
		return checkWord(params[0]);

	case COMMAND_MODIFY_WORD:
		if (params.size() != 2)
			return STATE_ERROR;
		return checkWord(params[0]) * checkWord(params[1]);

	case COMMAND_PRE_PAGE:
		if (currentPage == 0)
			return STATE_ERROR;
		return STATE_NORMAL;

	case COMMAND_NEXT_PAGE:
		if (currentPage == textFile_->getPageList().size() - 1)
			return STATE_ERROR;
		return STATE_NORMAL;

	case COMMAND_SAVE_FILE:
		return STATE_NORMAL;

	default:
		return STATE_ERROR;
	}

}

void ConsoleIO::handlingCommand(string command) {

	char commandType = command[0];
	string paramsText = command.substr(2, command.size() - 2);
	vector<string> params = splitParameters(paramsText);

	state = checkUserInput(commandType, params);

	if (state == STATE_ERROR)
		return;

	switch (commandType) {
	case COMMAND_INSERT_WORD:
		insertWord(params);
		break;
	case COMMAND_DELETE_WORD:
		delWord(params);
		break;
	case COMMAND_RESTRUCT_PAGE:
		restructByWord(params);
		break;
	case COMMAND_MODIFY_WORD:
		modifyAllWord(params);
		break;
	case COMMAND_PRE_PAGE:
		printPage(--currentPage);
		break;
	case COMMAND_NEXT_PAGE:
		printPage(++currentPage);
		break;
	case COMMAND_SAVE_FILE:
		saveFile();
		break;
	}

}


void ConsoleIO::insertWord(vector<string> params) {
	int lineNum = atoi(params[0].c_str());
	int wordNum = atoi(params[1].c_str());
	int idx = GlobalWordList::getInstance()->getIndex(lineNum, wordNum);
	
	GlobalWordList::getInstance()->insertWord(idx, params[2]);
}

void ConsoleIO::delWord(vector<string> params) {
	int lineNum = atoi(params[0].c_str());
	int wordNum = atoi(params[1].c_str());
	int idx = GlobalWordList::getInstance()->getIndex(lineNum, wordNum);

	GlobalWordList::getInstance()->delWord(idx);
}

void ConsoleIO::modifyAllWord(vector<string> params) {
	GlobalWordList::getInstance()->modifyAllWord(params[0], params[1]);
}

void ConsoleIO::restructByWord(vector<string> params) {
	int idx = GlobalWordList::getInstance()->getIndex(params[0]);
	textFile_->restructPageList(GlobalWordList::getInstance()->getWordList(), idx);
}

void ConsoleIO::saveFile() {

}

void ConsoleIO::printPage(int pageNo) {
	int lineBeginIdx = getBeginLineNum(pageNo) + 1;
	vector<string> page = textFile_->getPageList().at(pageNo);
	int lineNumInPage = page.size();

	for(int lineIter = 0; lineIter < pageNo; lineIter++) {
		cout << setw(2) << lineBeginIdx << "|\t" << page[lineIter] << endl;
	}
	cout << CUTOFF_LINE << endl << COMMAND_HELP_MESSAGE << endl << CUTOFF_LINE << endl;

}
int ConsoleIO::getBeginLineNum(int pageNo) {
	int lineNum = 0;
	
	for (int pageIdx = 0; pageIdx < pageNo; pageIdx++) {
		lineNum += textFile_->getPageList().at(pageIdx).size();
	}
	return lineNum;
}
