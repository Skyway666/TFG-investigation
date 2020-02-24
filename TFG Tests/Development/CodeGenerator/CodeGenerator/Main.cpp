
#include "FileSystem.h"
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
	BOOL,
	ARRAY
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

bool tokenIsType(TokenType type) {
	return type == TokenType::TY_BOOL || type == TokenType::TY_CHAR || type == TokenType::TY_INT || type == TokenType::TY_VOID;
}

Type token2Type(TokenType type) {

	Type ret = Type::NULL_TYPE;

	switch (type) {
		case TokenType::TY_BOOL:
			ret = Type::BOOL;
			break;
		case TokenType::TY_CHAR:
			ret = Type::STRING;
			break;
		case TokenType::TY_INT:
			ret = Type::INT;
			break;
		case TokenType::TY_VOID:
			ret = Type::VOID;
			break;
	}

	return ret;
}


struct PProperty {
	char name[MAX_NAME_CHARS];
	Type type = Type::NULL_TYPE;

	Type arrayType = Type::NULL_TYPE;
	int arraySize = 0; // IN MEMORY. To get size of elements -> arraySize / enum2sizeof(arrayType)

	void Parse(Token* tokens, int* currentToken) {
		// Current token is the Property type

		type = token2Type(tokens[*currentToken].type);
		bool nameFound = false;

		(*currentToken)++; // Go passed the type specifier

		while (tokens[*currentToken].type != TokenType::SEP_SEMICOL) {

			if (tokens[*currentToken].type == TokenType::USER_BIT && !nameFound) {
				strcpy_s(name, MAX_NAME_CHARS, tokens[*currentToken].name);
				nameFound = true;
			}
			if (tokens[*currentToken].type == TokenType::SEP_OPEN_ARR) {
				// Look for the next "user bit" and convert the string to a number. This is the array size.
			}

			(*currentToken)++;
		}

		(*currentToken)++; // Go passed the semicolon
	}
};

struct PMethod {
	char name[MAX_NAME_CHARS];

	Type returnValue = Type::NULL_TYPE;
	int argumentsIndex = 0;
	Type arguments[MAX_ARGUMENTS];

	void Parse(Token* tokens, int* currentToken) {
		// Current token is the return value specifier

		returnValue = token2Type(tokens[*currentToken].type);
		bool nameFound = false;

		(*currentToken)++; // Go passed the return value

		while (tokens[*currentToken].type != TokenType::SEP_SEMICOL) {

			if (tokens[*currentToken].type == TokenType::USER_BIT && !nameFound) {
				strcpy_s(name, MAX_NAME_CHARS, tokens[*currentToken].name);
				nameFound = true;
			}

			if (tokenIsType(tokens[*currentToken].type)) {
				// This is an argument
				arguments[argumentsIndex++] = token2Type(tokens[*currentToken].type);
			}

			(*currentToken)++; 
		}

		(*currentToken)++; // Go passed the semicolon
	}

};

struct PClass {
	char name[MAX_NAME_CHARS];

	int propertyIndex = 0;
	PProperty properties[MAX_PROPERTIES];

	int methodIndex = 0;
	PMethod methods[MAX_METHODS];

	void Parse(Token* tokens, int* currentToken) {
		// For the moment we are only looking at one class/ file

		bool nameFound = false;

		while (tokens[*currentToken].type != TokenType::NULL_TOKEN) {

			if (tokens[*currentToken].type == TokenType::USER_BIT && !nameFound) {
				strcpy_s(name, MAX_NAME_CHARS, tokens[*currentToken].name);
				nameFound = true;
			}

			if (tokenIsType(tokens[*currentToken].type)) {
				// We have either a method or a property
				int i = *currentToken;
				bool isMethod = false;
				while (true) {
					if (tokens[i].type == TokenType::SEP_OPEN_FUNC){
						isMethod = true;
						break;
					}
					if (tokens[i].type == TokenType::SEP_SEMICOL)
						break;
					i++;
				}

				if(isMethod){
					// It's a method
					PMethod method;
					method.Parse(tokens, currentToken);
					methods[methodIndex++] = method;
				}
				else {
					// It's a property
					PProperty property;
					property.Parse(tokens, currentToken);
					properties[propertyIndex++] = property;
				}

			}
			(*currentToken)++;
		}

	}

};




Token parseSeparationTokken(char character) {

	Token ret = Token(TokenType::NULL_TOKEN);

	if (character == '\n' || character == '\r' || character == '\t' || character == ' ')
		ret = Token(TokenType::SEP_SPACE);
	else if(character == '[')
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

int main() {
	
	// LEXER/TOKENIZER

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

		// Both the token and space have been added
		tokenCount++;

		if (clearBit) {
			for (int i = 0; i < MAX_NAME_CHARS; i++)
				Bit[i] = '\0';
			bitCount = 0;
		}
	}

	// PARSER

	// Looking for a class
		
	int currentToken = 0;
	// For the moment we are only looking at one class/ file
	PClass classDefinition;
	while (tokens[currentToken].type != TokenType::NULL_TOKEN) {

		if (tokens[currentToken].type == TokenType::KW_CLASS) {
			classDefinition.Parse(tokens, &currentToken);
		}


		currentToken++;
	}

	return 0;
}