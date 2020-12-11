#pragma once

#define MAX_LINE_NUM					20
#define MAX_LINE_SIZE					75

#define CHAR_DOUBLE_QUOTATION_MARK		34
#define CHAR_SINGLE_QUOTATION_MARK		39
#define CHAR_BACKSLASH					92

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
#define COMMAND_HELP_MESSAGE	"n:���� ������, p:���� ������, i:����, d:����, c:����, s:ã��, t:���� �� ����"

#define ERR_MSG_FILE_NOT_FOUND	"������ ã�� �� �����ϴ�.\n"
#define ERR_MSG_COMMAND_TYPE	"�߸��� ����Դϴ�.\n"
#define ERR_MSG_PARAMETER_VAL	"�Ķ���� ���� ��ȿ���� �ʽ��ϴ�.\n"
#define ERR_MSG_PARAMETER_NUM	"�Ķ���� ������ ���� �ʽ��ϴ�.\n"
#define ERR_MSG_NOT_FOUND_WORD	"�ش� �ܾ ã�� ���߽��ϴ�.\n"
#define ERR_MSG_OUT_OF_INDEX	"�ش� �ε����� ã�� ���߽��ϴ�.\n"
#define ERR_MSG_OUT_OF_PAGE		"�ش� �������� �̵� �Ұ��մϴ�.\n"

#define ERR_MSG_RE_INPUT		"�ٽ� �Է��ϼ���. \n"
#define ERR_MSG_TERMINATE		"�����մϴ�. \n"

enum ErrorType {
	NOT_ERROR = 0,
	ERROR_FILE_NOT_FOUND = 1,
	ERROR_INPUT_LENGTH,
	ERROR_COMMAND_TYPE,
	ERROR_PARAMETER_NUM,
	ERROR_PARAMETER_VAL,
	ERROR_OUT_OF_PAGE,
	ERROR_OUT_OF_INDEX,
	ERROR_NOT_FOUND_WORD
};

using namespace std;
