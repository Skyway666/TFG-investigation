

#include "Reflection.h"
#include "MyClass.h"



// Automatically generated


// FUNCTION REFLECTION: TODO(Lucas): Rename so function overload is supported
void MyClassFuncWrap_sum1ToA() {
	TypeInfo* metadata = Reflection::getMetadataFor("MyClass");
	MethodDataHolder methodDataHolder = metadata->methodDataHolder;

	*(int*)methodDataHolder.returnPointer = ((MyClass*)methodDataHolder.instancePointer)->sum1ToA(*(bool*)methodDataHolder.argumentsPointers[0]);
}

// Fill "TypeInfo metadata" for MyClass: TODO(Lucas): Consider returning integer with the position of the newly registered metadata
void registerMyClassForReflection() {
	
	TypeInfo* metadata = &Reflection::metadata[Reflection::metadata_index++];

	// Name

	metadata->name = "MyClass";
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


