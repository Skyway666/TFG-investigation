

#include "Reflection.h"
#include "MyClass.h"



// Automatically generated


// FUNCTION REFLECTION: TODO(Lucas): Rename so function overload is supported
void MyClassFuncWrap_sum1ToA_BOOL() {
	TypeInfo* metadata = Reflection::getMetadataFor("MyClass");
	MethodDataHolder mdh = metadata->methodDataHolder;

	*(int*)mdh.returnPointer = ((MyClass*)mdh.instancePointer)->sum1ToA(*(bool*)mdh.argumentsPointers[0]);
}

void MyClassFuncWrap_addNumbers_INT_INT() {
	TypeInfo* metadata = Reflection::getMetadataFor("MyClass");
	MethodDataHolder methodDataHolder = metadata->methodDataHolder;

	*(int*)methodDataHolder.returnPointer = ((MyClass*)methodDataHolder.instancePointer)->addNumbers(*(int*)methodDataHolder.argumentsPointers[0], *(int*)methodDataHolder.argumentsPointers[1]);
}

void MyClassFuncWrap_addNumbers_INT_INT_INT() {
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

	// Add "name" field (a char*)
	metadata->pushProperty(Property("name", offsetof(MyClass, MyClass::name), TypeDef(Type::CHAR, -1, true)));

	// Add "message" field (a char array)
	metadata->pushProperty(Property("message", offsetof(MyClass, MyClass::message), TypeDef(Type::CHAR, 150)));

	// Add "numbers" field
	metadata->pushProperty(Property("numbers", offsetof(MyClass, MyClass::numbers), TypeDef(Type::INT, 3 * (int)sizeof(int))));


	//METHODS

	// Add "void sum1ToA(bool)" method
	Method method;
	method.function_wrapper = &MyClassFuncWrap_sum1ToA_BOOL;
	method.def.name = "sum1ToA";
	method.def.returnValue = Type::INT;

	method.def.pushArgument(Type::BOOL);

	metadata->pushMethod(method);
	method.clear();

	// Add "int addNumbers(int, int)" method
	method.function_wrapper = &MyClassFuncWrap_addNumbers_INT_INT;
	method.def.name = "addNumbers";
	method.def.returnValue = Type::INT;

	method.def.pushArgument(Type::INT);
	method.def.pushArgument(Type::INT);

	metadata->pushMethod(method);
	method.def.clear();

	// Add "int addNumbers(int, int, int)" method
	method.function_wrapper = &MyClassFuncWrap_addNumbers_INT_INT_INT;
	method.def.name = "addNumbers";
	method.def.returnValue = Type::INT;

	method.def.pushArgument(Type::INT);
	method.def.pushArgument(Type::INT);
	method.def.pushArgument(Type::INT);

	metadata->pushMethod(method);
}


