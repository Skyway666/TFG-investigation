#include "Tokenizer.h"
#include "Parser.h"
#include "CodeGenerator.h"
#include "Third Party/parson.h"

/* This function will fill:

	- outputDirectory (global variable)
	- inputDirectory (in the main stack)
	- objects (global variable) 
*/
void loadConfig(const char** inputDirectory) {
	// Parson
	JSON_Value* rawFile = json_parse_file("config.json");
	JSON_Object* file = json_value_get_object(rawFile);
	JSON_Array* jsonReflectedObjects = json_object_get_array(file, "reflected-objects");


	outputDirectory = json_object_get_string(file, "output-directory");
	*inputDirectory = json_object_get_string(file, "input-directory");

	int reflectedObjectsCount = json_array_get_count(jsonReflectedObjects);
	for (int i = 0; i < reflectedObjectsCount; i++) {
		const char* reflectedObjectName = json_array_get_string(jsonReflectedObjects, i);
		strcpy_s(objects[objectsIndex++], MAX_NAME_CHARS, reflectedObjectName);
	}
}

int main() {

	// TOOL CONFIGURATION

	// Declared locally, since there is no need to use it elsewhere
	const char* inputDirectory = nullptr;
	loadConfig(&inputDirectory);


	// TOOL CYCLE FOR 1 FILE -> TODO(Lucas): Iterate input directory

	// LEXER/TOKENIZER
	char parsedFileName[MAX_FILE_NAME_CHARS];
	strcpy_s(parsedFileName, MAX_NAME_CHARS, inputDirectory);
	strcat_s(parsedFileName, "/MyClass.h");

	Token tokens[TEN_THOUSEND];
	tokenizeFile(parsedFileName, tokens);

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