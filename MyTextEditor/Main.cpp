#include "GlobalWordList.h"
#include "ConsoleIO.h"
#include <iostream>

using namespace std;

int main() {
	ConsoleIO console;
	
	try {
		console.loadTextFile("C://Users//kisti_user//Desktop//test.txt");
		console.printPage(0);
		cout << GlobalWordList::getInstance()->wordListSize() << endl;

	}
	catch (string& str) {
		cout << str << endl;
		return -1;
	}
	
	string command;
	while (!console.state) {
		cout << "입력 : ";
		cin >> command;
		console.handlingCommand(command);
		
		if(console.state == STATE_ERROR)
			cout << "다시 입력하세요." << endl;
	}

	//cout << GlobalWordList::getInstance()->wordListSize() << endl;

	return 1;
}