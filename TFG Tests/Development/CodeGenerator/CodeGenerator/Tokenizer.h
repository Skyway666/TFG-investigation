#pragma once
#include "Globals.h"
#include "FileSystem.h"


Token parseSeparationTokken(char character) {

	Token ret = Token(TokenType::NULL_TOKEN);

	if (character == '\n' || character == '\r' || character == '\t' || character == ' ')
		ret = Token(TokenType::SEP_SPACE);
	else if (character == '[')
		ret = Token(TokenType::SEP_OPEN_ARR);
	else if (character == ']')
		ret = Token(TokenType::SEP_CLOSE_ARR);
	else if (character == '{')
		ret = Token(TokenType::SEP_OPEN_DEF);
	else if (character == '}')
		ret = Token(TokenType::SEP_CLOSE_DEF);
	else if (character == '(')
		ret = Token(TokenType::SEP_OPEN_FUNC);
	else if (character == ')')
		ret = Token(TokenType::SEP_CLOSE_FUNC);
	else if (character == '*')
		ret = Token(TokenType::SEP_POINTER);
	else if (character == ':')
		ret = Token(TokenType::SEP_COL);
	else if (character == ';')
		ret = Token(TokenType::SEP_SEMICOL);
	else if (character == '=')
		ret = Token(TokenType::OP_ASSIGN);
	else if (character == '+')
		ret = Token(TokenType::OP_SUM);
	else if (character == '-')
		ret = Token(TokenType::OP_SUBST);

	return ret;
}

void tokenizeFile(const char* file, Token* tokens) {
	char* code = nullptr;
	int codeSize = 0;
	codeSize = ImportFileString(file, &code);

	// Array for words with each analysed character
	char Bit[MAX_NAME_CHARS];
	int bitCount = 0;

	// Array with all the generated tokkens
	int tokenCount = 0;

	for (int i = 0; i < codeSize; i++) {

		// Fill bit to analyse it later
		Bit[bitCount++] = code[i];
		bool clearBit = false;
		// Characters that indicate the end of a tokken (also a tokken themselves): Spaces, array keys, def keys, function keys, pointers, ':', ';'

		// Detect separators
		if (code[i] == '\n' || code[i] == '\r' || code[i] == '\t' || code[i] == ' ' ||
			code[i] == '[' || code[i] == ']' || code[i] == '{' || code[i] == '}' ||
			code[i] == '(' || code[i] == ')' || code[i] == '*' || code[i] == ':' || code[i] == ';' ||
			code[i] == '=' || code[i] == '+' || code[i] == '-') {

			bool nothingBehindSpace = false;
			bitCount - 1 == 0 ? nothingBehindSpace = true : tokenCount++;

			// Allways add tokken of spearation
			tokens[tokenCount] = parseSeparationTokken(code[i]);

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
			tokens[tokenCount - 1] = Token(TokenType::TY_VOID);
		}
		// Ints
		else if (strcmp(Bit, "int") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::TY_INT);
		}
		// Bools
		else if (strcmp(Bit, "bool") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::TY_BOOL);
		}
		// Chars
		else if (strcmp(Bit, "char") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::TY_CHAR);
		}


		// Class
		else if (strcmp(Bit, "class") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::KW_CLASS);
		}
		// Struct
		else if (strcmp(Bit, "struct") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::KW_STRUCT);
		}
		// Public
		else if (strcmp(Bit, "public") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::KW_PUBLIC);
		}
		// Private
		else if (strcmp(Bit, "private") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::KW_PRIVATE);
		}
		// Const
		else if (strcmp(Bit, "const") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::KW_CONST);
		}
		// Unsigned
		else if (strcmp(Bit, "unsigned") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::KW_UNSIGNED);
		}


		// Detect Defines
		else if (strcmp(Bit, "#define") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::SP_DEFINE);
		}
		// Detect IfnDef
		else if (strcmp(Bit, "#ifndef") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::SP_IFNDEF);
		}
		// Detect Includes
		else if (strcmp(Bit, "#include") == 0) {
			tokens[tokenCount - 1] = Token(TokenType::SP_INCLUDE);
		}
		// If the word is nothing parsable, it must be A "USER_BIT" (function, variable, class...)
		else {
			Token user_bit = Token(TokenType::USER_BIT);

			strcpy_s(user_bit.name, bitCount, Bit);
			tokens[tokenCount - 1] = user_bit;
		}

		// Both the token and space have been added
		tokenCount++;

		if (clearBit) {
			for (int i = 0; i < MAX_NAME_CHARS; i++)
				Bit[i] = '\0';
			bitCount = 0;
		}
	}
}

