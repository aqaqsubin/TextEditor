#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "GlobalWordList.h"
#include "TextFileIO.h"

using namespace std;

TextFileIO::TextFileIO(string path) {
	ifstream in(path);

	string readBuffer;

	if (in.is_open()) {
		getline(in, readBuffer);
		text.append(readBuffer).append(" ");
	}

	in.close();
}

void TextFileIO::createWordList(char delimiter) {
	vector<string> wordList;

	stringstream strStream(text);
	string word;

	while (getline(strStream, word, delimiter)) {
		wordList.push_back(word);
	}

	GlobalWordList::getInstance()->setWordList(wordList);
}

void TextFileIO::createTextFile() {

}
