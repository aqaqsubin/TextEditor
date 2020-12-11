#include <vector>
#include <string>
#include "cdEditor.h"

class GlobalWordList {

private:
	static GlobalWordList* s_instance;
	vector<string> wordList_;
	GlobalWordList();
	GlobalWordList(const GlobalWordList& instance);
	GlobalWordList& operator=(const GlobalWordList& instance);

public:
	static GlobalWordList* getInstance();

	void setWordList(vector<string>& wordList);

	vector<string>& getWordList();

	void insertWord(int idx, string word);

	void delWord(int idx);

	void modifyAllWord(string word, string newWord);

	int getIndex(string word);

	int getIndex(int lineNum, int wordNum);

};


