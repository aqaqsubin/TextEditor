#include "GlobalWordList.h"
#include "TextFileIO.h"
#include <iostream>

using namespace std;

int main() {

	TextFileIO fileIO("C://Users//kisti_user//Desktop//test.txt");
	fileIO.createWordList(' ');

	cout << GlobalWordList::getInstance()->wordListSize() << endl;

	return 1;
}