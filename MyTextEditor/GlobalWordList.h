#include <vector>
#include <string>


using namespace std;

class GlobalWordList {

private:
	static GlobalWordList* s_instance;
	vector<string> wordList_;
	GlobalWordList();
	GlobalWordList(vector<string>& wordList);
	GlobalWordList(const GlobalWordList& instance);
	GlobalWordList& operator=(const GlobalWordList& instance);

public:
	static GlobalWordList* getInstance();
	void setWordList(vector<string>& wordList);

	vector<string>& getWordList();
	vector<string>& getSubWordList(int beginIdx, int endIdx);

	int wordListSize();

	void insertWord(int idx, string word);

	void delWord(int idx);

	void modifyWord(int idx, string newWord);
	void modifyAllWord(string word, string newWord);
	int getIndex(string word);
	int getIndex(int lineNum, int wordNum);

};


