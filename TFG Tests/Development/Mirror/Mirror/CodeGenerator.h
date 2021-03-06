#pragma once
#include "Globals.h"
#include "Parser.h"
#include "FileSystem.h"
#include "IncrustatedTypeInfo.h"

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
		case Type::CHAR:
			return "CHAR";
		break;
		case Type::OBJECT:
			return "OBJECT";
		break;
	}

	return nullptr;
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
	case Type::CHAR:
		return "char";
		break;
	}

	return nullptr;
}

void writeFunctionDeclaration(std::ofstream& cpp, char* className, PMethod method) {

	cpp  << className << "FuncWrap_";

	cpp << method.name;
	for (int i = 0; i < method.argumentCount; i++) {
		Type argument = method.arguments[i];
		cpp << "_" << type2String(method.arguments[i]);
	}
}

bool supportCheck(PMethod& method) {
	if (method.returnType == Type::OBJECT)
		return false;

	for (int i = 0; i < method.argumentCount; i++) {
		if (method.arguments[i] == Type::OBJECT)
			return false;
	}

	return true;
}

void openFiles(char headerFiles[][MAX_FILE_NAME_CHARS], int headerFilesCount) {
	std::ofstream header(outputH, std::ofstream::app);

	header << "#ifndef ";
	header << "REFLECTION" << std::endl;

	header << "#define ";
	header << "REFLECTION" << std::endl << std::endl;

	header << typeInfoCode;

	header.close();

	std::ofstream cpp(outputCPP, std::ofstream::app);

	cpp << "#include \"Reflection.h\"" << std::endl;

	for (int i = 0; i < headerFilesCount; i++) {
		// Generate path relative to output-directory
		char includePath[MAX_FILE_NAME_CHARS];
		relativePath(headerFiles[i], outputDirectory, includePath);

		cpp << "#include \"" << includePath << "\"" << std::endl;
	}

	cpp.close();
}

void generateCode(PObject object) {

	// Header
	std::ofstream header(outputH, std::ofstream::app);

	header << std::endl << std::endl;
	header << "// Register function for " << object.name;
	header << std::endl;

	header << "void register";
	header << object.name;
	header << "ForReflection();" << std::endl << std::endl;

	header.close();

	// Cpp
	std::ofstream cpp(outputCPP, std::ofstream::app);
	cpp << std::endl << std::endl;
	cpp << "// Reflection code for " << object.name;
	cpp << std::endl;

	// METHODS WRAPPERS
	for (int i = 0; i < object.methodCount; i++) {

		PMethod method = object.methods[i];

		// TODO: Support methods with pointers or objects as arguments/return value 
		if (!supportCheck(method))
			continue;

		cpp << "void ";
		writeFunctionDeclaration(cpp, object.name, method);
		cpp << "() {";
		cpp << std::endl;
		// Open "ClassNameFuncWrap_functionName_ARGUMENT1TYPE_ARGUMENT2TYPE...()
		cpp << "TypeInfo* metadata = Mirror::getMetadataFor(\"" << object.name << "\");" << std::endl;
		cpp << "MethodDataHolder mdh = metadata->methodDataHolder;" << std::endl << std::endl;

		if (method.returnType != Type::VOID) {
			cpp << "*(" << type2Ctype(method.returnType) << "*)mdh.returnPointer = ";
		}

		cpp << "((" << object.name << "*)mdh.instancePointer)->" << method.name << "(";

		for (int i = 0; i < method.argumentCount; i++) {
			Type argument = method.arguments[i];

			cpp << "*(" << type2Ctype(argument) << "*)mdh.argumentPointers[" << std::to_string(i) << "]";
			if (i != method.argumentCount - 1) {
				cpp << ", ";
			}

		}
		cpp << ");";

		// Close "ClassNameFuncWrap_functionName_ARGUMENT1TYPE_ARGUMENT2TYPE...()
		cpp << std::endl;
		cpp << "}";

		cpp << std::endl << std::endl;
	}



	cpp << "void register";
	cpp << object.name;
	cpp << "ForReflection(){" << std::endl;
	// Open "registerClassNameForReflection()"

	// PROPS REFLECTION
	cpp << "TypeInfo* metadata = &Mirror::metadata[Mirror::metadataIndex++];" << std::endl << std::endl;

	cpp << "metadata->name = " << "\"" <<object.name << "\";" << std::endl << std::endl;

	for (int i = 0; i < object.propertyCount; i++) {
		PProperty prop = object.properties[i];

		cpp << "metadata->pushProperty(Property(\"" << prop.name << "\", ";
		cpp << "offsetof(" << object.name << ", " << object.name << "::" << prop.name << "), ";

		bool notBasic = prop.isPointer || prop.arraySize[0] != 0 || prop.type == Type::OBJECT;

		if (notBasic) {
			cpp << "TypeDef(";

		}
		
		cpp << "Type::" << type2String(prop.type);

		if (prop.type == Type::OBJECT) {
			cpp << ", \"" << prop.objectName << "\"";
		}

		if (prop.arraySize[0] != '\0') {
			cpp << ", ";
			cpp << prop.arraySize << " * (int)sizeof(" << (prop.type != Type::OBJECT ? type2Ctype(prop.type) : prop.objectName);
			if (prop.isPointer)
				cpp << "*";
			cpp << ")";
		}

		if (prop.isPointer) {
			cpp << ", " << "true";
		}

		if (notBasic) {
			cpp << ")";
		}

		cpp << "));" << std::endl;

	}
	cpp << std::endl;

	// METHOD REFLECTION

	if(object.methodCount != 0)
		cpp << "Method method;" << std::endl;

	for (int i = 0; i < object.methodCount; i++) {
		PMethod method = object.methods[i];

		if (!supportCheck(method)) 
			continue;

		cpp << "method.function_wrapper = &";
		writeFunctionDeclaration(cpp, object.name, method);
		cpp << ";" << std::endl;
		cpp << "method.def.name = \"" << method.name << "\";" << std::endl;
		cpp << "method.def.returnType = Type::" << type2String(method.returnType) << ";" << std::endl;

		for (int i = 0; i < method.argumentCount; i++) {
			cpp << "method.def.pushArgument(Type::" << type2String(method.arguments[i]) << ");" << std::endl;
		}
		cpp << std::endl;
		cpp << "metadata->pushMethod(method);" << std::endl;
		cpp << "method.def.clear();" << std::endl << std::endl;

	}


	// Close "registerClassForReflection()"
	cpp << "}" << std::endl;
	cpp.close();
}

void closeFiles() {

	// Header
	std::ofstream header(outputH, std::ofstream::app);
	header << std::endl << std::endl;

	// RegisterAll declaration
	header << "// Global register function" << std::endl;
	header << "void registerALLForReflection();" << std::endl << std::endl;
	header << std::endl << std::endl << "#endif //REFLECTION";
	header.close();

	std::ofstream cpp(outputCPP, std::ofstream::app);

	// Reflection statics declaration
	const char* reflectionStatics = R"(TypeInfo Mirror::metadata[];
int Mirror::metadataIndex = 0;

Mirror::Mirror() {
}


Mirror::~Mirror() {
}


TypeInfo* Mirror::getMetadataFor(const char* objectName) {

	for (int i = 0; i < metadataIndex; i++)
		if (strcmp(objectName, metadata[i].name) == 0)
			return &metadata[i];

	return nullptr;
})";

	cpp << std::endl;
	cpp << reflectionStatics << std::endl << std::endl;

	// RegisterAll definition
	cpp << "void registerALLForReflection() {" << std::endl << std::endl;

	for (int i = 0; i < parsedObjectsIndex; i++) {
		cpp << "register" << parsedObjects[i] << "ForReflection();";
		cpp << std::endl;
	}

	cpp << std::endl << "}";

	cpp.close();
}