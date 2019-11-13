

#include "MyClass.h"
// Automatically generated

TypeInfo MyClass::metadata;

// Fill "TypeInfo"
void MyClass::registerForReflection() {
	

	TypeInfo metadata = MyClass::metadata;

	// Add "int b" field
	int offset = offsetof(MyClass, MyClass::b); // Method to calculate offset works

	metadata.pushProperty(new Property("b", offset, Type::INT));

}




