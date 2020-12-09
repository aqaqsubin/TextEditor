#pragma once
#include <string>

#define MAX_LINE_NUM		20
#define MAX_LINE_SIZE		75

using namespace std;


class TextFile {
private:
	vector<vector<string>> pageList;
	string text_;

public:
	TextFile(string path);

	vector<string>& createWordList(char delimiter);

	void setPageList(vector<string> wordList);

	void restructPageList(vector<string> wordList, int searchWordIdx);

	vector<vector<string>>& getPageList();

	void saveTextFile();

};