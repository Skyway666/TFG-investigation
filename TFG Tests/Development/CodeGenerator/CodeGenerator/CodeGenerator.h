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
	for (int i = 0; i < method.argumentsIndex; i++) {
		Type argument = method.arguments[i];
		cpp << "_" << type2String(method.arguments[i]);
	}
}

bool supportCheck(PMethod& method) {
	if (method.returnValue == Type::OBJECT)
		return false;

	for (int i = 0; i++; i < method.argumentsIndex) {
		if (method.arguments[i] == Type::OBJECT)
			return false;
	}

	return true;
}

void generateCode(PObject object) {

	// Header
	char headerName[MAX_NAME_CHARS];

	if(outputDirectory)
		strcpy_s(headerName, MAX_NAME_CHARS, outputDirectory);

	strcat_s(headerName, "/Reflection.h");

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
	char cppName[MAX_NAME_CHARS];
	if (outputDirectory)
		strcpy_s(cppName, MAX_NAME_CHARS, outputDirectory);

	strcat_s(cppName, "/Reflection.cpp");

	std::ofstream cpp(cppName);

	cpp << "#include \"Reflection.h\"" << std::endl;
	cpp << "#include \"";
	// TODO(Lucas): Maybe let the user define the route, to customize file location
	cpp << headerName << "\"";
	cpp << std::endl << std::endl;

	// METHODS WRAPPERS
	for (int i = 0; i < object.methodIndex; i++) {

		PMethod method = object.methods[i];

		// TODO: Support methods with pointers or objects as arguments/return value 
		if (!supportCheck(method))
			continue;

		cpp << "void ";
		writeFunctionDeclaration(cpp, object.name, method);
		cpp << "() {";
		cpp << std::endl;
		// Open "ClassNameFuncWrap_functionName_ARGUMENT1TYPE_ARGUMENT2TYPE...()
		cpp << "TypeInfo* metadata = Reflection::getMetadataFor(\"" << object.name << "\");" << std::endl;
		cpp << "MethodDataHolder mdh = metadata->methodDataHolder;" << std::endl << std::endl;

		if (method.returnValue != Type::VOID) {
			cpp << "*(" << type2Ctype(method.returnValue) << "*)mdh.returnPointer = ";
		}

		cpp << "((" << object.name << "*)mdh.instancePointer)->" << method.name << "(";

		for (int i = 0; i < method.argumentsIndex; i++) {
			Type argument = method.arguments[i];

			cpp << "*(" << type2Ctype(argument) << "*)mdh.argumentPointers[" << std::to_string(i) << "]";
			if (i != method.argumentsIndex - 1) {
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
	cpp << "TypeInfo* metadata = &Reflection::metadata[Reflection::metadataIndex++];" << std::endl << std::endl;

	cpp << "metadata->name = " << object.name << std::endl << std::endl;

	for (int i = 0; i < object.propertyIndex; i++) {
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
	cpp << "Method method;" << std::endl;

	for (int i = 0; i < object.methodIndex; i++) {
		PMethod method = object.methods[i];

		if (!supportCheck(method)) 
			continue;

		cpp << "method.function_wrapper = &";
		writeFunctionDeclaration(cpp, object.name, method);
		cpp << ";" << std::endl;
		cpp << "method.def.name = \"" << method.name << "\";" << std::endl;
		cpp << "method.def.returnValue = Type::" << type2String(method.returnValue) << ";" << std::endl;

		for (int i = 0; i < method.argumentsIndex; i++) {
			cpp << "method.def.pushArgument(Type::" << type2String(method.arguments[i]) << ");" << std::endl;
		}
		cpp << std::endl;
		cpp << "metadata->pushMethod(method);" << std::endl;
		cpp << "method.def.clear()" << std::endl << std::endl;

	}


	// Close "registerClassForReflection()"
	cpp << "}" << std::endl;
	cpp.close();
	

}