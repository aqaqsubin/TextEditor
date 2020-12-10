#include "GlobalWordList.h"
#include "ConsoleIO.h"
#include <iostream>

int main() {
	ConsoleIO console;
	
	try {
		console.loadTextFile("C://Users//aqaq9//Documents//TextEditor//test.txt");
		console.printPage(0);
	}
	catch (string& str) {
		cout << str << endl;
		return -1;
	}
	
	string command;
	while (console.state) {
		cout << "ют╥б : ";
		cin >> command;
		cout << CUTOFF_LINE << endl;

		console.handlingCommand(command);
		
		if (console.state == STATE_ERROR) {
			console.printError();
		}
	}

	cout << "end" << endl;

	return 1;
}