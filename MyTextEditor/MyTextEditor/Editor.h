#include "TextFile.h"
#include "cdEditor.h"
#include <string>
#include <vector>

#pragma once
class Editor {

private:
	TextFile* textFile_;
	vector<string> params_;
	
	char commandType_;
	int currentPage = 0;
	
	int loadCommand(string command);

	int checkLineNum(string paramLineNum);
	int checkWordNum(string paramWordNum);
	int checkWord(string word);

	int checkCommandValid(char commandType, vector<string> params);

	int insertWord(vector<string> params);

	int delWord(vector<string> params);

	int modifyAllWord(vector<string> params);

	int restructByWord(string param);

	int restorePageList();

	void saveFile();

	int getBeginLineNum(int pageNo);

public:
	int state = 1;
	ErrorType errorType;
	
	void loadTextFile(string path);

	void handlingCommand(string command);

	void printPrePage();

	void printPage();

	void printNextPage();

	void printError();

};