#pragma once
#include "Globals.h"
#include "Parser.h"
#include "FileSystem.h"

void generateCode(PClass object) {

	// Header
	char fileName[MAX_NAME_CHARS];

	strcpy_s(fileName, MAX_NAME_CHARS, object.name);
	

	strcat_s(fileName, ".generated.h");
	std::ofstream header(fileName);

	header << "I'm going to reflect ";
	header << object.name;

	// Cpp
}