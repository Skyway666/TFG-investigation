

#include "MyClass.h"
// Automatically generated

TypeInfo MyClass::metadata;

// Fill "TypeInfo"
void MyClass::registerForReflection() {
	
	TypeInfo* metadata = &MyClass::metadata;

	// Add "int a" field
	int offset = offsetof(MyClass, MyClass::a); 
	metadata->pushProperty(Property("a", offset, Type::INT));

	// Add "int b" field
	 offset = offsetof(MyClass, MyClass::b); 
	metadata->pushProperty(Property("b", offset, Type::INT));

	// Add "bool is" field
	offset = offsetof(MyClass, MyClass::is);
	metadata->pushProperty(Property("is", offset, Type::BOOL));
}






