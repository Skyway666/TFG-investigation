#pragma once
#include "Globals.h"
#include "Parser.h"
#include "FileSystem.h"

const char* type2String(Type type) {

	switch (type) {
		case Type::VOID:
			return "VOID";
		break;
		case Type::INT:
			return "INT";
		break;
		case Type::BOOL:
			return "BOOL";
		break;
		case Type::STRING:
			return "STRING";
		break;
		case Type::CONST_STRING:
			return "CONST_STRING";
		break;
	}
}

const char* type2Ctype(Type type) {

	switch (type) {
	case Type::VOID:
		return "void";
		break;
	case Type::INT:
		return "int";
		break;
	case Type::BOOL:
		return "bool";
		break;
	case Type::STRING:
		return "char";
		break;
	case Type::CONST_STRING:
		return "const char*";
		break;

	}
}

void writeFunctionDeclaration(std::ofstream& cpp, char* className, PMethod method) {

	cpp << "void " << className << "FuncWrap_";

	cpp << method.name;
	for (int i = 0; i < method.argumentsIndex; i++) {
		Type argument = method.arguments[i];
		cpp << "_" << type2String(method.arguments[i]);
	}

	cpp << "() {";
	cpp << std::endl;
}

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

	// METHODS WRAPPERS
	for (int i = 0; i < object.methodIndex; i++) {

		PMethod method = object.methods[i];

		writeFunctionDeclaration(cpp, object.name, method);
		// Open "ClassNameFuncWrap_functionName_ARGUMENT1TYPE_ARGUMENT2TYPE...()
		cpp << "char whatHappens[100] = \"Function implementation\";";
		cpp << std::endl;
		cpp << "}";
		cpp << std::endl << std::endl;
	}




	cpp << "void register";
	cpp << object.name;
	cpp << "ForReflection(){" << std::endl;
	// Open "registerClassNameForReflection()"

	// PROPS REFLECTION
	cpp << "TypeInfo* metadata = &Reflection::metadata[Reflection::metadataIndex++];" << std::endl << std::endl;

	cpp << "metadata->name = " << object.name << std::endl << std::endl;

	for (int i = 0; i < object.propertyIndex; i++) {
		PProperty prop = object.properties[i];

		cpp << "metadata->pushProperty(Property(\"" << prop.name << "\", ";
		cpp << "offsetof(" << object.name << ", " << object.name << "::" << prop.name << "), ";
		cpp << "Type::" << type2String(prop.type);

		if (prop.arraySize[0] != '\0') {
			cpp << ", ";
			cpp << prop.arraySize << " * sizeof(" << type2Ctype(prop.type) << ")";
		}

		cpp << "));" << std::endl;

	}

	cpp << "}" << std::endl;

	// METHOD REFLECTION



	// Close "registerClassForReflection()"

	cpp.close();
	

}