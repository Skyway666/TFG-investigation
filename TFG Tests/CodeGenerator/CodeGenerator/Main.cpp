
#include "FileSystem.h"
#define MAX_NAME_CHARS
enum TokenType {
	TY_INT,
	TY_VOID,
	TY_BOOL,
	TY_CHAR,
	TY_POINTER,
	KW_OPEN_FUNC, //'('
	KW_CLOSE_FUNC, // ')'
	KW_OPEN_DEF, // '{'
	KW_CLOSE_DEF, // '}'
	KW_OPEN_ARR, // [
	KW_CLOSE_ARR, // ]
	KW_CLASS,
	KW_STRUCT,
	KW_PUBLIC,
	KW_PRIVATE,
	KW_STATIC,
	KW_CONST,
	KW_UNSIGNED,
	USER_NAME
};

class Token {
	TokenType type;
	char name[];
};


int main() {
	
	char* code = ImportFileString("ParsedFiles/MyClass.h");

	return 0;
}