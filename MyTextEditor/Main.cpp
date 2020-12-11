#include "GlobalWordList.h"
#include "Editor.h"
#include <iostream>

int main() {
	Editor console;
	
	try {
		console.loadTextFile("C://Users//aqaq9//Documents//TextEditor//test.txt");
		console.printPage();
	}
	catch (string& str) {
		console.printError();
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