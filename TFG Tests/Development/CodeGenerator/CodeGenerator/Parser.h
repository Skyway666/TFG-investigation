#pragma once
#include "Globals.h"

bool tokenIsType(Token token) {
	TokenType type = token.type;
	char* name = token.name;

	// If it is a USER_BIT, we might be working with an Object. 
	// We need to check if it matches any of the classes that the user has defined for reflection
	if (type == TokenType::USER_BIT) {
		for (int i = 0; i < objectsIndex; i++) {
			if (strcmp(name, objects[i]) == 0)
				return true;
		}
	}

	return type == TokenType::TY_BOOL || type == TokenType::TY_CHAR || type == TokenType::TY_INT || type == TokenType::TY_VOID;
}

Type token2Type(TokenType type) {

	Type ret = Type::NULL_TYPE;

	switch (type) {
	case TokenType::TY_BOOL:
		ret = Type::BOOL;
		break;
	case TokenType::TY_CHAR:
		ret = Type::CHAR;
		break;
	case TokenType::TY_INT:
		ret = Type::INT;
		break;
	case TokenType::TY_VOID:
		ret = Type::VOID;
		break;
	case TokenType::USER_BIT:
		ret = Type::OBJECT;
		break;
	}

	return ret;
}

struct PProperty {
	char name[MAX_NAME_CHARS];
	Type type = Type::NULL_TYPE;

	char arraySize[MAX_DIGITS]; // IN MEMORY. To get size of elements -> arraySize / enum2sizeof(arrayType)
	bool isPointer = false;
	char objectName[MAX_NAME_CHARS];

	void Parse(Token* tokens, int* currentToken) {
		// Current token is the Property type


		type = token2Type(tokens[*currentToken].type);
		// Get arrays ready to use for Code Generator
		arraySize[0] = '\0';
		objectName[0] = '\0';

		if(type == Type::OBJECT)
			strcpy_s(objectName, MAX_NAME_CHARS, tokens[*currentToken].name);

		(*currentToken)++; // Go passed the type specifier
		
		// Boolean needed in order to not overwrite "name" if more user bits are found
		bool nameFound = false;

		while (tokens[*currentToken].type != TokenType::SEP_SEMICOL) {

			
			if (tokens[*currentToken].type == TokenType::USER_BIT && !nameFound) {
				strcpy_s(name, MAX_NAME_CHARS, tokens[*currentToken].name);
				nameFound = true;
			}
			// We have found a '*', the variable must be a pointer
			if (tokens[*currentToken].type == TokenType::SEP_POINTER) {
				isPointer = true;
			}
			
			if (tokens[*currentToken].type == TokenType::SEP_OPEN_ARR) {
				// Look for the next "user bit" and convert the string to a number. This is the array size.
				while (tokens[*currentToken].type != TokenType::USER_BIT) {
					(*currentToken)++;
				}
				strcpy_s(arraySize, MAX_DIGITS, tokens[*currentToken].name);
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

			if (tokenIsType(tokens[*currentToken])) {
				// This is an argument
				arguments[argumentsIndex++] = token2Type(tokens[*currentToken].type);
			}

			(*currentToken)++;
		}

		(*currentToken)++; // Go passed the semicolon
	}

};

struct PObject {
	char name[MAX_NAME_CHARS];

	int propertyIndex = 0;
	PProperty properties[MAX_PROPERTIES];

	int methodIndex = 0;
	PMethod methods[MAX_METHODS];

	void ParseName(Token* tokens, int* currentToken) {
		while (tokens[*currentToken].type != TokenType::USER_BIT)
			(*currentToken)++;

		strcpy_s(name, MAX_NAME_CHARS, tokens[*currentToken].name);
		// Go passed the name of the class
		(*currentToken)++;

	}

	void Parse(Token* tokens, int* currentToken) {
		// For the moment we are only looking at one class/ file
		while (tokens[*currentToken].type != TokenType::KW_CLASS && tokens[*currentToken].type != TokenType::NULL_TOKEN) {

			if (tokenIsType(tokens[*currentToken])) {
				// We have either a method or a property
				int i = *currentToken;
				bool isMethod = false;
				while (true) {
					if (tokens[i].type == TokenType::SEP_OPEN_FUNC) {
						isMethod = true;
						break;
					}
					if (tokens[i].type == TokenType::SEP_SEMICOL)
						break;
					i++;
				}

				// Method or property
				if (isMethod)
					methods[methodIndex++].Parse(tokens, currentToken);
				else 
					properties[propertyIndex++].Parse(tokens, currentToken);

			}
			(*currentToken)++;
		}

	}

};