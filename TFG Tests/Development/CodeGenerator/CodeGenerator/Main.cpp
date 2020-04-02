
#include "Tokenizer.h"
#include "Parser.h"
#include "CodeGenerator.h"

int main() {
	
	// LEXER/TOKENIZER
	Token tokens[TEN_THOUSEND];
	tokenizeFile("../ParsedFiles/MyClass.h", tokens);

	// PARSER
	// Looking for a class
	int currentToken = 0;
	// For the moment we are only looking at one class/ file
	PClass classDefinition;
	while (tokens[currentToken].type != TokenType::NULL_TOKEN) {

		if (tokens[currentToken].type == TokenType::KW_CLASS) {
			classDefinition.Parse(tokens, &currentToken);
			break;
		}
		currentToken++;
	}

	// Code Generator
	generateCode(classDefinition);

	return 0;
}