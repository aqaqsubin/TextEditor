#include "TextFile.h"
#include "cdEditor.h"
#include <string>
#include <vector>

enum ErrorType{
	NOT_ERROR= 0,
	ERROR_PARAMETER_NUM = 1,
	ERROR_PARAMETER_VAL,
	ERROR_OUT_OF_PAGE,
	ERROR_OUT_OF_INDEX,
	ERROR_NOT_FOUND_WORD,
	ERROR_COMMAND_TYPE
};

#pragma once
class ConsoleIO {
public:
	int state = 1;
	ErrorType errorType;
	int currentPage = 0;
	TextFile* textFile_;

	void loadTextFile(string path);

	vector<string> splitParameters(string paramsText);

	int checkLineNum(string paramLineNum);
	int checkWordNum(string paramWordNum);
	int checkWord(string word);

	int checkUserInput(char commandType, vector<string> params);

	void handlingCommand(string command);

	int insertWord(vector<string> params);

	int delWord(vector<string> params);

	int modifyAllWord(vector<string> params);

	int restructByWord(vector<string> params);

	void saveFile();

	void printPage(int pageNo);

	void printError();

	int getBeginLineNum(int pageNo);

};