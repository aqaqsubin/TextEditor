#include "GlobalWordList.h"
#include "ConsoleIO.h"
#include <iostream>

using namespace std;

int main() {
	ConsoleIO console;
	console.loadTextFile("C://Users//aqaq9//Desktop//test.txt");
	cout << GlobalWordList::getInstance()->wordListSize() << endl;
	console.printPage(0);

	string command;
	while (!console.state) {
		cout << "�Է� : ";
		cin >> command;
		console.handlingCommand(command);
		
		if(console.state == STATE_ERROR)
			cout << "�ٽ� �Է��ϼ���." << endl;
	}

	//cout << GlobalWordList::getInstance()->wordListSize() << endl;

	return 1;
}