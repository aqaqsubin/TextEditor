#include <vector>
#include <string>

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class GlobalWordList {

private:
	static GlobalWordList* s_instance;
	vector<string> wordList_;
	GlobalWordList() {
	}
	GlobalWordList(vector<string> &wordList) {
		wordList_ = wordList;
	}
	GlobalWordList(const GlobalWordList& instance);
	GlobalWordList& operator=(const GlobalWordList& instance);

public:
	static GlobalWordList* getInstance() {
		if (!s_instance)
			s_instance = new GlobalWordList;
		return s_instance;
	}
	void setWordList(vector<string>& wordList) {
		wordList_ = wordList;
	}
	vector<string>& getSubWordList(int beginIdx, int endIdx) {
		vector<string> subWordList;
		subWordList.assign(wordList_.begin() + beginIdx, wordList_.end() + endIdx);
		return subWordList;
	}
	int wordListSize() {
		return wordList_.size();
	}
	void insertWord(int idx, string word) {
		wordList_.insert(wordList_.begin() + idx, word);
	}
	void delWord(int idx) {
		wordList_.erase(wordList_.begin()+idx);
	}
	void modifyWord(int idx, string newWord) {
		
		delWord(idx);
		insertWord(idx, newWord);
	}
	void modifyAllWord(string word, string newWord) {
		for (int i = 0; i < wordList_.size(); i++) {
			if (wordList_[i] == word) {
				delWord(i);
				insertWord(i, newWord);
			}
		}
	}
	int getIndex(string word) {
		for (int i = 0; i < wordList_.size();i++ ) {
			if (wordList_[i] == word)
				return i;
		}
		return -1;
	}
	int getIndex(int lineNum, int wordNum) {

		int lineIter = 1;
		int sumOfByte = 0;

		int wordIter = 1;
		int numOfWordInLine = 1;

		for (int i = 0; i < wordList_.size(); i++) {
			if (lineIter == lineNum && numOfWordInLine == wordNum)
				return i;
			
			if (sumOfByte + wordList_[i].size()  + 1 >= 75){
				lineIter++;
				sumOfByte = 0;
			}
			sumOfByte += wordList_[i].size() + 1;
			numOfWordInLine++;
			
		}
		return -1;
	}

};

GlobalWordList *GlobalWordList::s_instance = 0;

class TextFileIO {
private :
	string text;

public:
	TextFileIO(string path) {
		ifstream in(path);
		
		string readBuffer;

		if (in.is_open()) {
			getline(in, readBuffer);
			text.append(readBuffer).append(" ");
		}

		in.close();
	}

	void createWordList(char delimiter) {
		vector<string> wordList;

		stringstream strStream(text);
		string word;

		while (getline(strStream, word, delimiter)) {
			wordList.push_back(word);
		}

		GlobalWordList::getInstance()->setWordList(wordList);
	}

	void createTextFile() {
		
	}
};
class ConsoleIO {
private:
	

public:
	bool checkInputError(string userInput) {

	}
	bool handlingCommand(string userInput) {

	}
	bool restructText(string inputParams) {

	}
	
	
};

int main() {

	TextFileIO fileIO("C://Users//aqaq9//Desktop//test.txt");
	fileIO.createWordList(' ');

	cout << GlobalWordList::getInstance()->wordListSize() << endl;
	
	return 1;
}