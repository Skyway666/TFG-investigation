

#include "MyClass.generated.h"
#include "MyClass.h"
// Automatically generated

// Fill "TypeInfo"
void MyClass::registerForReflection() {
	

	TypeInfo metadata = MyClass::metadata; //Link error



	// Add "int b" field

	int offset = offsetof(MyClass, MyClass::b); // Method to calculate offset works

	StringWithLength name;
	name.string = (char*)"a";
	name.length = 2;

	metadata.properties.push_back(Property(name, offset, Type::INT));

}

TypeInfo MyClass::metadata;

