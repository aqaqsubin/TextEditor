#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <iomanip>
#include "GlobalWordList.h"
#include "TextFile.h"

TextFile::TextFile(string path) {

	filePath_ = path;
	ifstream in(filePath_);

	string readBuffer;

	if (in.is_open()) {
		getline(in, readBuffer);
		text_.append(readBuffer).append(" ");
	}
	else
		throw string(ERR_MSG_FILE_NOT_FOUND);

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

		if (sumOfByte + wordList[i].size() > MAX_LINE_SIZE) {
			page.push_back(line);

			line.clear();
			lineIter++;
			sumOfByte = 0;
		}
		if (lineIter > MAX_LINE_NUM) {
			pageList.push_back(page);
			page.clear();
			lineIter = 1;
		}
		sumOfByte += wordList[i].size();
		line.append(wordList[i]);
		if (sumOfByte < MAX_LINE_SIZE) {
			sumOfByte += 1;
			line.append(" ");
		}
	}
}
vector<vector<string>> TextFile::getPageList() {
	return pageList;
}
int TextFile::restructPageList(vector<string> wordList, int searchWordIdx) {
	int sumOfByte = 0;

	int lineIter = 1;
	int pageIdx = 0;
	vector<string> page;
	string line;

	page.clear();
	pageList.clear();
	for (int i = 0; i < wordList.size(); i++) {
		if (sumOfByte + wordList[i].size() > MAX_LINE_SIZE) {
			page.push_back(line);

			line.clear();
			lineIter++;
			sumOfByte = 0;
		}
		if (lineIter > MAX_LINE_NUM) {
			pageList.push_back(page);

			page.clear();
			lineIter = 1;
		}
		if (i == searchWordIdx && sumOfByte) {
			page.push_back(line);
			line.clear();
			sumOfByte = 0;

			pageList.push_back(page);
			pageIdx = pageList.size();

			page.clear();
			lineIter = 1;
		}
		sumOfByte += wordList[i].size();
		line.append(wordList[i]);
		if (sumOfByte < MAX_LINE_SIZE) {
			sumOfByte += 1;
			line.append(" ");
		}
	}
	return pageIdx;
}

void TextFile::saveTextFile(vector<string>& wordList) {
	text_.clear();
	for (int idx = 0; idx < wordList.size()-1; idx++) 
		text_.append(wordList[idx]).append(" ");
	
	text_.append(wordList[wordList.size() - 1]);

	ofstream out(filePath_);
	if (out.is_open())
		out << text_;

}