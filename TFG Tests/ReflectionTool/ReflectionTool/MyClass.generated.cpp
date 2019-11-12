

#include "MyClass.h"
// Automatically generated

// Fill "TypeInfo
void MyClass::registerForReflection() {
	
	TypeInfo info_instance;
	TypeInfo* metadata = &info_instance;

	//TypeInfo* metadata = &MyClass::metadata; //Link error

	MyClass instance;
	MyClass* classPointer = &instance;

	// Add "int b" field

	int offset = (int)&classPointer->b - (int)classPointer; // Method to calculate offset works

	StringWithLength name;
	name.string = (char*)"a";
	name.length = 2;

	metadata->properties.push_back(Property(name, offset, Type::INT));

}

