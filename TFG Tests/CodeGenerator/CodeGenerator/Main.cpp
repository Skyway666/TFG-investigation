
#include "FileSystem.h"
#include <string>
#define MAX_NAME_CHARS 30
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
	KW_CLASS,
	KW_STRUCT,
	KW_PUBLIC,
	KW_PRIVATE,
	KW_STATIC,
	KW_CONST,
	KW_UNSIGNED,
};

struct Token {
	// Constructors
	Token(): type(TokenType::NULL_TOKEN){}
	Token(TokenType type): type(type){}

	TokenType type;

	// int number of line = 0;

	// Probably  use dynamic memory, most tokkens don't need a name but some of them do
	char name[MAX_NAME_CHARS] = { '\0' };
};




int main() {
	
	char* code = nullptr;
	int codeSize = 0;
	codeSize = ImportFileString("ParsedFiles/MyClass.h", &code);

	// Array for words with each analysed character
	char Bit[MAX_NAME_CHARS];
	int bitCount = 0;

	// Array with all the generated tokkens
	Token tokens[TEN_THOUSEND];
	int tokenCount = 0;

	for (int i = 0; i < codeSize; i++) {

		// Fill bit to analyse it later
		Bit[bitCount++] = code[i];
		bool clearBit = false; 
		// Characters that indicate the end of a tokken (also a tokken themselves): Spaces, array keys, def keys, function keys, pointers, ':', ';'

		// Detect spaces
		if (code[i] == '\n' || code[i] == '\r' || code[i] == '\t' || code[i] == ' ') {

			bool nothingBehindSpace = false;
			bitCount - 1 == 0 ? nothingBehindSpace = true : tokenCount++;

			// Allways add tokken of space
			tokens[tokenCount] = Token(TokenType::SEP_SPACE);

			// Nothing behind the space, go for next iteration
			if (nothingBehindSpace) {
				tokenCount++;
				bitCount = 0;
				continue;
			}

			// Get tokken ready to be parsed
			Bit[bitCount - 1] = '\0';
			// Next iteration will write the bit from scratch
			clearBit = true;
		}
		else
			continue; // If there is no separation just continue adding characters to "Bit"

		// Tokkens before separation tokkens

		// Void
		if (strcmp(Bit, "void") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::TY_VOID);;
		}
		// Ints
		else if (strcmp(Bit, "int") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::TY_INT);;
		}
		// Bools
		else if (strcmp(Bit, "bool") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::TY_BOOL);;
		}
		// Chars
		else if (strcmp(Bit, "char") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::TY_CHAR);;
		}


		// Class
		else if (strcmp(Bit, "class") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::KW_CLASS);;
		}
		else if (strcmp(Bit, "struct") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::KW_STRUCT);;
		}
		else if (strcmp(Bit, "public:") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::KW_PUBLIC);;
		}
		else if (strcmp(Bit, "private:") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::KW_PRIVATE);;
		}

		// Detect Defines
		else if (strcmp(Bit, "#define") == 0) {
			tokens[tokenCount-1] = Token(TokenType::SP_DEFINE);
		}
		// Detect IfnDef
		else if (strcmp(Bit, "#ifndef") == 0) {
			tokens[tokenCount-1] = Token(TokenType::SP_IFNDEF);
		}
		// Detect Includes
		else if (strcmp(Bit, "#include") == 0) {
			tokens[tokenCount-1] = Token(TokenType::SP_INCLUDE);
		}
		// If the word is nothing parsable, it must be A "USER_BIT" (function, variable, class...)
		else {
			Token user_bit = Token(TokenType::USER_BIT);

			strcpy_s(user_bit.name, bitCount, Bit);
			tokens[tokenCount - 1] = user_bit;
		}

		if (clearBit) {
			for (int i = 0; i < MAX_NAME_CHARS; i++)
				Bit[i] = '\0';
			bitCount = 0;
		}
		


	}


	return 0;
}