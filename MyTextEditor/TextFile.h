#pragma once
#include <string>
#include "cdEditor.h"


class TextFile {
private:
	vector<vector<string>> pageList;
	string filePath_;
	string text_;

public:
	TextFile(string path);

	vector<string> createWordList(char delimiter);

	void setPageList(vector<string>& wordList);

	int restructPageList(vector<string> wordList, int searchWordIdx);

	vector<vector<string>> getPageList();

	void saveTextFile(vector<string>& wordList);

};