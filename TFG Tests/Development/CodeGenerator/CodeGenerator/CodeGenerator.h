#pragma once
#include "Globals.h"
#include "Parser.h"
#include "FileSystem.h"

void generateCode(PClass object) {

	// Header
	char headerName[MAX_NAME_CHARS];
	strcpy_s(headerName, MAX_NAME_CHARS, object.name);
	strcat_s(headerName, ".generated.h");

	std::ofstream header(headerName);

	header << "#ifndef ";
	header << object.name;
	header << "CLASS" << std::endl;

	header << "#define ";
	header << object.name;
	header << "CLASS" << std::endl << std::endl;

	header << "void register";
	header << object.name;
	header << "ForReflection();" << std::endl << std::endl;

	header << "#endif //";
	header << object.name;
	header << "CLASS";

	header.close();

	// Cpp

	// rename file
	char cppName[MAX_NAME_CHARS];
	strcpy_s(cppName, MAX_NAME_CHARS, object.name);
	strcat_s(cppName, ".generated.cpp");

	std::ofstream cpp(cppName);

	cpp << "#include \"Reflection.h\"" << std::endl;
	cpp << "#include \"";
	// Maybe let the user define the route, to customize file location
	cpp << headerName << "\"";
	cpp << std::endl << std::endl;


	cpp << "void register";
	cpp << object.name;
	// Open "registerXXXXForReflection()"
	cpp << "ForReflection(){" << std::endl;

	cpp << "// I have initialized an integer automatically :)" << std::endl;
	cpp << "int a = 2;" << std::endl;

	cpp << "}" << std::endl;
	// Close "registerXXXXForReflection()"
	

}