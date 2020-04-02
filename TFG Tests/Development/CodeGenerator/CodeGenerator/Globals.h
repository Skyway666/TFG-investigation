#pragma once

#include <string>
#define MAX_NAME_CHARS 30
#define MAX_PROPERTIES 30
#define MAX_METHODS 30
#define MAX_ARGUMENTS 10
#define TEN_THOUSEND 10000

enum TokenType {
	NULL_TOKEN,
	USER_BIT, // Goes with name 
	C_STR, // Goes with name
	TY_INT,
	TY_VOID,
	TY_BOOL,
	TY_CHAR,
	SP_DEFINE,
	SP_IFNDEF,
	SP_INCLUDE,
	SP_COMMENT,
	SEP_SPACE,
	SEP_OPEN_FUNC, //'('
	SEP_CLOSE_FUNC, // ')'
	SEP_OPEN_DEF, // '{'
	SEP_CLOSE_DEF, // '}'
	SEP_OPEN_ARR, // [
	SEP_CLOSE_ARR, // ]
	SEP_COL, // :
	SEP_SEMICOL, // ;
	SEP_POINTER, // *
	OP_ASSIGN, // =
	OP_SUM, // +
	OP_SUBST, // -
	KW_CLASS,
	KW_STRUCT,
	KW_PUBLIC,
	KW_PRIVATE,
	KW_STATIC,
	KW_CONST,
	KW_UNSIGNED,

};

enum Type {
	NULL_TYPE,
	VOID,
	INT,
	CONST_STRING,
	STRING,
	BOOL
};

struct Token {
	// Constructors
	Token() : type(TokenType::NULL_TOKEN) {}
	Token(TokenType type) : type(type) {}

	TokenType type;

	// int number of line = 0;

	// Probably  use dynamic memory, most tokkens don't need a name but some of them do
	char name[MAX_NAME_CHARS] = { '\0' };
};