

#include "MyClass.h"

// Temporal static member of the reflected class, should be stored in a list.
TypeInfo MyClass::metadata;



// Automatically generated


// FUNCTION REFLECTION
void MyClassFuncWrap_sum1ToA() {
	TypeInfo* metadata = &MyClass::metadata;
	MethodDataHolder methodDataHolder = metadata->methodDataHolder;

	*(int*)methodDataHolder.returnPointer = ((MyClass*)methodDataHolder.instancePointer)->sum1ToA(*(bool*)methodDataHolder.argumentsPointers[0]);
}

// Fill "TypeInfo metadata"
void MyClass::registerForReflection() {
	
	TypeInfo* metadata = &MyClass::metadata;

	// FIELDS

	// Add "int a" field
	metadata->pushProperty(Property("a", offsetof(MyClass, MyClass::a), Type::INT));

	// Add "int b" field
	metadata->pushProperty(Property("b", offsetof(MyClass, MyClass::b), Type::INT));

	// Add "bool is" field
	metadata->pushProperty(Property("is", offsetof(MyClass, MyClass::is), Type::BOOL));

	// Add "name" field
	metadata->pushProperty(Property("name", offsetof(MyClass, MyClass::name), Type::CONST_STRING));

	// Add "message" field
	metadata->pushProperty(Property("message", offsetof(MyClass, MyClass::message), Type::STRING));

	// Add "numbers" field
	Property numbers = Property("numbers", offsetof(MyClass, MyClass::numbers), Type::ARRAY);
	numbers.arrayType = Type::INT;
	numbers.arraySize = 3 * sizeof(int);
	metadata->pushProperty(numbers);


	//METHODS

	// Add "sum1ToA" method
	Method method;
	method.function_wrapper = &MyClassFuncWrap_sum1ToA;
	method.name = "sum1ToA";
	method.returnValue = Type::INT;
	// Maybe it could be just "pushArgument()"
	method.argumentCount = 1;
	method.arguments[0] = Type::BOOL;

	metadata->pushMethod(method);
}


