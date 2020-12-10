#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <iomanip>
#include "GlobalWordList.h"
#include "TextFile.h"


#include <iostream>
using namespace std;

TextFile::TextFile(string path) {
	ifstream in(path);

	string readBuffer;
	
	if (in.is_open()) {
		getline(in, readBuffer);
		
		for (int cIdx = 0; cIdx < readBuffer.size(); cIdx++) {
			if (static_cast<int> (readBuffer[cIdx]) == CHAR_DOUBLE_QUOTATION_MARK || static_cast<int>(readBuffer[cIdx]) == CHAR_SINGLE_QUOTATION_MARK) {
				string backslash;
				backslash += static_cast<char> (CHAR_BACKSLASH);
				
				readBuffer.insert(cIdx, backslash);
			}
		}
		text_.append(readBuffer).append(" ");
	}
	else
		throw string("File Cannot Open");

	in.close();
}

vector<string> TextFile::createWordList(char delimiter) {
	vector<string> wordList;

	stringstream strStream(text_);
	string word;

	while (getline(strStream, word, delimiter)) {
		wordList.push_back(word);
	}
	return wordList;
}

void TextFile::setPageList(vector<string>& wordList) {

	int sumOfByte = 0;

	int lineIter = 1;
	vector<string> page;
	string line;
	
	page.clear();
	pageList.clear();
	for (int i = 0; i < wordList.size(); i++) {
		try {
			if (sumOfByte + wordList[i].size() > MAX_LINE_SIZE) {
				page.push_back(line);

				line.clear();
				lineIter++;
				sumOfByte = 0;
			}
			if (lineIter > MAX_LINE_NUM) {
				pageList.insert(pageList.begin() + i, page);
				page.clear();
			}
			sumOfByte += wordList[i].size() + 1;
			if(sumOfByte < MAX_LINE_SIZE)
				line.append(wordList[i]).append(" ");
		}
		catch (...) {
			cout << i << endl;
		}

	}
	
}
vector<vector<string>>& TextFile::getPageList() {
	return pageList;
}
void TextFile::restructPageList(vector<string> wordList, int searchWordIdx) {
	int sumOfByte = 0;

	int lineIter = 1;
	vector<string> page;
	string line;

	for (int i = 0; i < wordList.size(); i++) {
		if (sumOfByte + wordList[i].size() + 1 >= MAX_LINE_SIZE) {
			page.insert(page.begin() + lineIter - 1, line);
			lineIter++;
			sumOfByte = 0;
		}
		if (lineIter > MAX_LINE_NUM || i == searchWordIdx) {
			pageList.insert(pageList.begin() + i, page);
			page.clear();
		}
		sumOfByte += wordList[i].size() + 1;
		line.append(wordList[i]).append(" ");

	}
}

void TextFile::saveTextFile() {

}