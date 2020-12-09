#include <vector>
#include <string>
#include "GlobalWordList.h"

using namespace std;

GlobalWordList::GlobalWordList() {
}
GlobalWordList::GlobalWordList(vector<string>& wordList) {
	wordList_ = wordList;
}

GlobalWordList* GlobalWordList::getInstance() {
	if (!s_instance)
		s_instance = new GlobalWordList;
	return s_instance;
}
void GlobalWordList::setWordList(vector<string>& wordList) {
	wordList_ = wordList;
}
vector<string>& GlobalWordList::getWordList() {
	return wordList_;
}
vector<string>& GlobalWordList::getSubWordList(int beginIdx, int endIdx) {
	vector<string> subWordList;
	subWordList.assign(wordList_.begin() + beginIdx, wordList_.end() + endIdx);
	return subWordList;
}
int GlobalWordList::wordListSize() {
	return wordList_.size();
}
void GlobalWordList::insertWord(int idx, string word) {
	wordList_.insert(wordList_.begin() + idx, word);
}
void GlobalWordList::delWord(int idx) {
	wordList_.erase(wordList_.begin() + idx);
}
void GlobalWordList::modifyWord(int idx, string newWord) {

	delWord(idx);
	insertWord(idx, newWord);
}
void GlobalWordList::modifyAllWord(string word, string newWord) {
	for (int i = 0; i < wordList_.size(); i++) {
		if (wordList_[i] == word) {
			delWord(i);
			insertWord(i, newWord);
		}
	}
}
int GlobalWordList::getIndex(string word) {
	for (int i = 0; i < wordList_.size(); i++) {
		if (wordList_[i] == word)
			return i;
	}
	return -1;
}
int GlobalWordList::getIndex(int lineNum, int wordNum) {

	int lineIter = 1;
	int sumOfByte = 0;

	int wordIter = 1;
	int numOfWordInLine = 1;

	for (int i = 0; i < wordList_.size(); i++) {
		if (lineIter == lineNum && numOfWordInLine == wordNum)
			return i;

		if (sumOfByte + wordList_[i].size() + 1 >= 75) {
			lineIter++;
			sumOfByte = 0;
		}
		sumOfByte += wordList_[i].size() + 1;
		numOfWordInLine++;

	}
	return -1;
}
GlobalWordList* GlobalWordList::s_instance = 0;