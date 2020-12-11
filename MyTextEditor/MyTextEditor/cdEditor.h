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
#define COMMAND_HELP_MESSAGE	"n:다음 페이지, p:이전 페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장 후 종료"

#define ERR_MSG_FILE_NOT_FOUND	"파일을 찾을 수 없습니다.\n"
#define ERR_MSG_COMMAND_TYPE	"잘못된 명령입니다.\n"
#define ERR_MSG_PARAMETER_VAL	"파라미터 값이 유효하지 않습니다.\n"
#define ERR_MSG_PARAMETER_NUM	"파라미터 개수가 맞지 않습니다.\n"
#define ERR_MSG_NOT_FOUND_WORD	"해당 단어를 찾지 못했습니다.\n"
#define ERR_MSG_OUT_OF_INDEX	"해당 인덱스를 찾지 못했습니다.\n"
#define ERR_MSG_OUT_OF_PAGE		"해당 페이지로 이동 불가합니다.\n"

#define ERR_MSG_RE_INPUT		"다시 입력하세요. \n"
#define ERR_MSG_TERMINATE		"종료합니다. \n"

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
