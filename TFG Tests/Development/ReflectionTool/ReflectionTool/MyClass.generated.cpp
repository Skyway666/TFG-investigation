

#include "Reflection.h"
#include "MyClass.h"



// Automatically generated


// FUNCTION REFLECTION: TODO(Lucas): Rename so function overload is supported
void MyClassFuncWrap_sum1ToA_bool() {
	TypeInfo* metadata = Reflection::getMetadataFor("MyClass");
	MethodDataHolder methodDataHolder = metadata->methodDataHolder;

	*(int*)methodDataHolder.returnPointer = ((MyClass*)methodDataHolder.instancePointer)->sum1ToA(*(bool*)methodDataHolder.argumentsPointers[0]);
}

void MyClassFuncWrap_addNumbers_int_int() {
	TypeInfo* metadata = Reflection::getMetadataFor("MyClass");
	MethodDataHolder methodDataHolder = metadata->methodDataHolder;

	*(int*)methodDataHolder.returnPointer = ((MyClass*)methodDataHolder.instancePointer)->addNumbers(*(int*)methodDataHolder.argumentsPointers[0], *(int*)methodDataHolder.argumentsPointers[1]);
}

void MyClassFuncWrap_addNumbers_int_int_int() {
	TypeInfo* metadata = Reflection::getMetadataFor("MyClass");
	MethodDataHolder methodDataHolder = metadata->methodDataHolder;

	*(int*)methodDataHolder.returnPointer = ((MyClass*)methodDataHolder.instancePointer)->addNumbers(*(int*)methodDataHolder.argumentsPointers[0], *(int*)methodDataHolder.argumentsPointers[1], *(int*)methodDataHolder.argumentsPointers[2]);
}


// Fill "TypeInfo metadata" for MyClass: TODO(Lucas): Consider returning integer with the position of the newly registered metadata
void registerMyClassForReflection() {
	
	TypeInfo* metadata = &Reflection::metadata[Reflection::metadataIndex++];

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
	metadata->pushProperty(Property("numbers", offsetof(MyClass, MyClass::numbers), Type::INT, 3 * sizeof(int)));


	//METHODS

	// Add "void sum1ToA(bool)" method
	Method method;
	method.function_wrapper = &MyClassFuncWrap_sum1ToA_bool;
	method.def.name = "sum1ToA";
	method.def.returnValue = Type::INT;
	// Maybe it could be just "pushArgument()"
	method.def.argumentCount = 1;
	method.def.arguments[0] = Type::BOOL;

	metadata->pushMethod(method);
	method.clear();

	// Add "int addNumbers(int, int)" method
	method.function_wrapper = &MyClassFuncWrap_addNumbers_int_int;
	method.def.name = "addNumbers";
	method.def.returnValue = Type::INT;
	// Maybe it could be just "pushArgument()"
	method.def.argumentCount = 2;
	method.def.arguments[0] = Type::INT;
	method.def.arguments[1] = Type::INT;

	metadata->pushMethod(method);

	// Add "int addNumbers(int, int, int)" method
	method.function_wrapper = &MyClassFuncWrap_addNumbers_int_int_int;
	method.def.name = "addNumbers";
	method.def.returnValue = Type::INT;
	// Maybe it could be just "pushArgument()"
	method.def.argumentCount = 3;
	method.def.arguments[0] = Type::INT;
	method.def.arguments[1] = Type::INT;
	method.def.arguments[2] = Type::INT;

	metadata->pushMethod(method);
}


