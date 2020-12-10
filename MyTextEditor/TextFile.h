#pragma once
#include <string>

#define MAX_LINE_NUM					20
#define MAX_LINE_SIZE					75

#define CHAR_DOUBLE_QUOTATION_MARK		34
#define CHAR_SINGLE_QUOTATION_MARK		39
#define CHAR_BACKSLASH					92

using namespace std;


class TextFile {
private:
	vector<vector<string>> pageList;
	

public:
	string text_;
	TextFile(string path);

	vector<string> createWordList(char delimiter);

	void setPageList(vector<string>& wordList);

	void restructPageList(vector<string> wordList, int searchWordIdx);

	vector<vector<string>>& getPageList();

	void saveTextFile();

};