#include "GlobalWordList.h"
#include "ConsoleIO.h"
#include <iostream>

int main() {
	ConsoleIO console;
	
	try {
		console.loadTextFile("C://Users//kisti_user//Documents//TextEditor//test.txt");
		console.printPage();
	}
	catch (string& str) {
		cout << str << endl;
		return -1;
	}
	
	string command;
	while (console.state) {
		cout << "ют╥б : ";
		getline(cin, command);
		cout << CUTOFF_LINE << endl;

		console.handlingCommand(command);
		console.printPage();
		if (console.state == STATE_ERROR) {
			console.printError();
		}
		
	}

	cout << "end" << endl;

	return 1;
}