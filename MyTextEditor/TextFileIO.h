#pragma once
#include <string>


using namespace std;

class TextFileIO {
private:
	string text;

public:
	TextFileIO(string path);

	void createWordList(char delimiter);

	void createTextFile();

};