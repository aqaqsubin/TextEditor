#include "TextFile.h"
#include <string>
#include <vector>

#define DELIMITER_WORD			' '
#define DELIMITER_PARAMETER		','
#define DELIMITER_NEW_LINE		'\n'

#define COMMAND_INSERT_WORD		'i'
#define COMMAND_DELETE_WORD		'd'
#define COMMAND_RESTRUCT_PAGE	's'
#define COMMAND_MODIFY_WORD		'c'

#define COMMAND_PRE_PAGE		'p'
#define COMMAND_NEXT_PAGE		'n'
#define COMMAND_SAVE_FILE		't'

#define STATE_NORMAL			1
#define STATE_TERMINATE			0
#define STATE_ERROR				-1

#define CUTOFF_LINE				"----------------------------------------------------------------------------"
#define COMMAND_HELP_MESSAGE	"n:다음 페이지, p:이전 페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장 후 종료"


using namespace std;

#pragma once
class ConsoleIO {
public:
	int state = 1;
	TextFile *textFile_;
	int currentPage = 0;

	void loadTextFile(string path);

	vector<string>& splitParameters(string paramsText);

	int checkLineNum(string paramLineNum);
	int checkWordNum(string paramWordNum);
	int checkWord(string word);

	int checkUserInput(char commandType, vector<string> params);
	
	void handlingCommand(string command);

	void insertWord(vector<string> params);

	void delWord(vector<string> params);

	void modifyAllWord(vector<string> params);

	void restructByWord(vector<string> params);

	void saveFile();

	void printPage(int pageNo);

	int getBeginLineNum(int pageNo);

};