#pragma once

#include "Globals.h"

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

	char arraySize[MAX_ARRAY_DIGITS]; // IN MEMORY. To get size of elements -> arraySize / enum2sizeof(arrayType)

	void Parse(Token* tokens, int* currentToken) {
		// Current token is the Property type

		type = token2Type(tokens[*currentToken].type);
		bool nameFound = false;
		bool pointerFound = false;
		arraySize[0] = '\0';

		(*currentToken)++; // Go passed the type specifier

		while (tokens[*currentToken].type != TokenType::SEP_SEMICOL) {

			// If we find a pointer we are probably working with a const char * (for the moment)
			if (tokens[*currentToken].type == TokenType::SEP_POINTER && !pointerFound) {
				if (type == Type::STRING) {
					type = Type::CONST_STRING;
				}
				pointerFound = true;
			}
			// Name of the variable
			if (tokens[*currentToken].type == TokenType::USER_BIT && !nameFound) {
				strcpy_s(name, MAX_NAME_CHARS, tokens[*currentToken].name);
				nameFound = true;
			}
			if (tokens[*currentToken].type == TokenType::SEP_OPEN_ARR) {
				// Look for the next "user bit" and convert the string to a number. This is the array size.
				while (tokens[*currentToken].type != TokenType::USER_BIT) {
					(*currentToken)++;
				}
				strcpy_s(arraySize, MAX_ARRAY_DIGITS, tokens[*currentToken].name);
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
					if (tokens[i].type == TokenType::SEP_OPEN_FUNC) {
						isMethod = true;
						break;
					}
					if (tokens[i].type == TokenType::SEP_SEMICOL)
						break;
					i++;
				}

				if (isMethod) {
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