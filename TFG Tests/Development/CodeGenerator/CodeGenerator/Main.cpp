#include "Tokenizer.h"
#include "Parser.h"
#include "CodeGenerator.h"
#include "Third Party/parson.h"

int main() {

	// TOOL CONFIGURATION
	strcpy_s(classes[classesIndex++], MAX_NAME_CHARS, "MyClass");
	strcpy_s(classes[classesIndex++], MAX_NAME_CHARS, "MyOtherClass");

	JSON_Value* rawFile = json_parse_file("config.json");

	JSON_Object* file = json_value_get_object(rawFile);
	const char* outputDirectory = json_object_get_string(file, "outputDirectory");
	

	
	// LEXER/TOKENIZER
	Token tokens[TEN_THOUSEND];
	tokenizeFile("../ParsedFiles/MyClass.h", tokens);

	// PARSER
	// Looking for a class
	int currentToken = 0;
	// For the moment we are only looking at one class/ file
	PObject classDefinition;
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