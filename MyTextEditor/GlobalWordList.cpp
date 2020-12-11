#include <vector>
#include <string>

#include "GlobalWordList.h"

using namespace std;

GlobalWordList::GlobalWordList() {
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

void GlobalWordList::insertWord(int idx, string word) {
	wordList_.insert(wordList_.begin() + idx, word);
}
void GlobalWordList::delWord(int idx) {
	wordList_.erase(wordList_.begin() + idx);
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
	for (int i = 0; i < wordList_.size(); i++) {
		if (sumOfByte + wordList_[i].size() > MAX_LINE_SIZE) {
			lineIter++;
			sumOfByte = 0;
			wordIter = 1;
		}
		if (lineIter == lineNum && wordIter == wordNum)
			return i;

		wordIter++;
		sumOfByte += wordList_[i].size();
		if (sumOfByte < MAX_LINE_SIZE) {
			sumOfByte += 1;
		}
	}
	
	return -1;
}
GlobalWordList* GlobalWordList::s_instance = 0;