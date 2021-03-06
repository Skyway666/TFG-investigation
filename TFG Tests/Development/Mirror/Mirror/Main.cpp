#include "Tokenizer.h"
#include "Parser.h"
#include "CodeGenerator.h"
#include "Third Party/parson.h"



/* This function will fill:

	- outputDirectory (global variable)
	- inputDirectory (in the main stack)
	- objects (global variable) 
*/
void loadConfig(char* inputDirectory) {
	// Parson
	JSON_Value* rawFile = json_parse_file("config.json");
	JSON_Object* file = json_value_get_object(rawFile);
	JSON_Array* jsonReflectedObjects = json_object_get_array(file, "reflected-objects");


	const char* tmp_outputDirectory = nullptr;
	if(json_object_has_value(file, "output-directory") == 1)
		tmp_outputDirectory = json_object_get_string(file, "output-directory");

	// Copy the output directory to a global variable for later use
	strcpy_s(outputDirectory, MAX_FILE_NAME_CHARS, tmp_outputDirectory);

	if(json_object_has_value(file, "input-directory") == 1)
		strcpy_s(inputDirectory, MAX_FILE_NAME_CHARS, json_object_get_string(file, "input-directory"));

	int reflectedObjectsCount = json_array_get_count(jsonReflectedObjects);
	for (int i = 0; i < reflectedObjectsCount; i++) {
		const char* reflectedObjectName = json_array_get_string(jsonReflectedObjects, i);
		strcpy_s(objects[objectsIndex++], MAX_NAME_CHARS, reflectedObjectName);
	}

	// Assemble output files

	if (tmp_outputDirectory) {
		strcpy_s(outputCPP, MAX_FILE_NAME_CHARS, tmp_outputDirectory);
		strcpy_s(outputH, MAX_FILE_NAME_CHARS, tmp_outputDirectory);

		strcat_s(outputH, "/Reflection.h");
		strcat_s(outputCPP, "/Reflection.cpp");
	}

	json_value_free(rawFile);
}

bool objectNeedsReflection(const char* objectName) {
		for (int i = 0; i < objectsIndex; i++)
			if (strcmp(objectName, objects[i]) == 0)
				return true;

		return false;
}
void generateReflection(const char* header) {

	// LEXER/TOKENIZER
	Token tokens[TEN_THOUSEND];
	tokenizeFile(header, tokens);

	// PARSER
	// Looking for a class
	int currentToken = 0;
	// For the moment we are only looking at one class/ file
	int classDefinitionsIndex = 0;
	PObject* classDefinitions = new PObject[MAX_OBJECTS];
	while (tokens[currentToken].type != TokenType::NULL_TOKEN) {

		if (tokenIsObject(tokens[currentToken])) {
			PObject* currentClass = &classDefinitions[classDefinitionsIndex++];

			// Go passed the class keyword
			currentToken++; 
			
			currentClass->ParseName(tokens, &currentToken);
			// Skip the parsing of object which don't need reflection
			if (!objectNeedsReflection(currentClass->name)) {
				classDefinitionsIndex--;
				continue;
			}


			currentClass->Parse(tokens, &currentToken);

			// Store this to generate global initialize function, once the class has been parsed
			strcpy_s(parsedObjects[parsedObjectsIndex++], MAX_NAME_CHARS, currentClass->name);

			// The object could have stopped parsing due to finding a new class, we don't want to skip it
			continue; 
		}
		currentToken++;
	}

	// CODE GENERATOR
	for(int i = 0; i < classDefinitionsIndex; i++)
		generateCode(classDefinitions[i]);

	delete classDefinitions;
}

int main() {

	// TOOL CONFIGURATION


	// Declared locally, since there is no need to use it elsewhere
	char inputDirectory[MAX_FILE_NAME_CHARS] = "";
	loadConfig(inputDirectory);

	// Clear the files that are going to be generated 
	remove(outputCPP);
	remove(outputH);

	// Get paths to header files
	int headerFilesIndex = 0;
	char headerFiles[MAX_FILES][MAX_FILE_NAME_CHARS];

	using std::filesystem::recursive_directory_iterator;
	for (auto& it : recursive_directory_iterator(inputDirectory)) {
		// Ignore directories
		if (it.status().type() == std::filesystem::file_type::directory)
			continue;

		std::string file = it.path().generic_string();

		if (checkExtension(file, "h")) {
			strcpy_s(headerFiles[headerFilesIndex++], MAX_FILE_NAME_CHARS, file.c_str());
		}
	}



	// Initialize generated files
		// includes
		// TypeInfo
		// header protection
	openFiles(headerFiles, headerFilesIndex);

	for (int i = 0; i < headerFilesIndex; i++) {
		generateReflection(headerFiles[i]);
	}

	closeFiles();

	return 0;
}