#include "Reflection.h"
#include "../ParsedFiles/MyClass.h"
#include "../ParsedFiles/MyOtherClass.h"


// Reflection code for MyClass
void MyClassFuncWrap_sum1ToA_BOOL() {
TypeInfo* metadata = Mirror::getMetadataFor("MyClass");
MethodDataHolder mdh = metadata->methodDataHolder;

*(int*)mdh.returnPointer = ((MyClass*)mdh.instancePointer)->sum1ToA(*(bool*)mdh.argumentPointers[0]);
}

void MyClassFuncWrap_addNumbers_INT_INT() {
TypeInfo* metadata = Mirror::getMetadataFor("MyClass");
MethodDataHolder mdh = metadata->methodDataHolder;

*(int*)mdh.returnPointer = ((MyClass*)mdh.instancePointer)->addNumbers(*(int*)mdh.argumentPointers[0], *(int*)mdh.argumentPointers[1]);
}

void MyClassFuncWrap_addNumbers_INT_INT_INT() {
TypeInfo* metadata = Mirror::getMetadataFor("MyClass");
MethodDataHolder mdh = metadata->methodDataHolder;

*(int*)mdh.returnPointer = ((MyClass*)mdh.instancePointer)->addNumbers(*(int*)mdh.argumentPointers[0], *(int*)mdh.argumentPointers[1], *(int*)mdh.argumentPointers[2]);
}

void MyClassFuncWrap_reference_BOOL() {
TypeInfo* metadata = Mirror::getMetadataFor("MyClass");
MethodDataHolder mdh = metadata->methodDataHolder;

*(int*)mdh.returnPointer = ((MyClass*)mdh.instancePointer)->reference(*(bool*)mdh.argumentPointers[0]);
}

void MyClassFuncWrap_getName_BOOL() {
TypeInfo* metadata = Mirror::getMetadataFor("MyClass");
MethodDataHolder mdh = metadata->methodDataHolder;

*(char*)mdh.returnPointer = ((MyClass*)mdh.instancePointer)->getName(*(bool*)mdh.argumentPointers[0]);
}

void registerMyClassForReflection(){
TypeInfo* metadata = &Mirror::metadata[Mirror::metadataIndex++];

metadata->name = "MyClass";

metadata->pushProperty(Property("a", offsetof(MyClass, MyClass::a), Type::INT));
metadata->pushProperty(Property("b", offsetof(MyClass, MyClass::b), Type::INT));
metadata->pushProperty(Property("is", offsetof(MyClass, MyClass::is), Type::BOOL));
metadata->pushProperty(Property("name", offsetof(MyClass, MyClass::name), TypeDef(Type::CHAR, true)));
metadata->pushProperty(Property("message", offsetof(MyClass, MyClass::message), TypeDef(Type::CHAR, 150 * (int)sizeof(char))));
metadata->pushProperty(Property("numbers", offsetof(MyClass, MyClass::numbers), TypeDef(Type::INT, 3 * (int)sizeof(int))));
metadata->pushProperty(Property("child", offsetof(MyClass, MyClass::child), TypeDef(Type::OBJECT, "MyOtherClass")));
metadata->pushProperty(Property("childPointer", offsetof(MyClass, MyClass::childPointer), TypeDef(Type::OBJECT, "MyOtherClass", true)));
metadata->pushProperty(Property("numberPointer", offsetof(MyClass, MyClass::numberPointer), TypeDef(Type::INT, true)));
metadata->pushProperty(Property("booleanPointers", offsetof(MyClass, MyClass::booleanPointers), TypeDef(Type::BOOL, 5 * (int)sizeof(bool*), true)));
metadata->pushProperty(Property("classes", offsetof(MyClass, MyClass::classes), TypeDef(Type::OBJECT, "MyOtherClass", 21 * (int)sizeof(MyOtherClass))));
metadata->pushProperty(Property("classArrays", offsetof(MyClass, MyClass::classArrays), TypeDef(Type::OBJECT, "MyOtherClass", 34 * (int)sizeof(MyOtherClass*), true)));

Method method;
method.function_wrapper = &MyClassFuncWrap_sum1ToA_BOOL;
method.def.name = "sum1ToA";
method.def.returnType = Type::INT;
method.def.pushArgument(Type::BOOL);

metadata->pushMethod(method);
method.def.clear();

method.function_wrapper = &MyClassFuncWrap_addNumbers_INT_INT;
method.def.name = "addNumbers";
method.def.returnType = Type::INT;
method.def.pushArgument(Type::INT);
method.def.pushArgument(Type::INT);

metadata->pushMethod(method);
method.def.clear();

method.function_wrapper = &MyClassFuncWrap_addNumbers_INT_INT_INT;
method.def.name = "addNumbers";
method.def.returnType = Type::INT;
method.def.pushArgument(Type::INT);
method.def.pushArgument(Type::INT);
method.def.pushArgument(Type::INT);

metadata->pushMethod(method);
method.def.clear();

method.function_wrapper = &MyClassFuncWrap_reference_BOOL;
method.def.name = "reference";
method.def.returnType = Type::INT;
method.def.pushArgument(Type::BOOL);

metadata->pushMethod(method);
method.def.clear();

method.function_wrapper = &MyClassFuncWrap_getName_BOOL;
method.def.name = "getName";
method.def.returnType = Type::CHAR;
method.def.pushArgument(Type::BOOL);

metadata->pushMethod(method);
method.def.clear();

}


// Reflection code for MyStructure
void registerMyStructureForReflection(){
TypeInfo* metadata = &Mirror::metadata[Mirror::metadataIndex++];

metadata->name = "MyStructure";

metadata->pushProperty(Property("struct_number", offsetof(MyStructure, MyStructure::struct_number), Type::INT));
metadata->pushProperty(Property("hasClass", offsetof(MyStructure, MyStructure::hasClass), Type::BOOL));

}


// Reflection code for MyOtherClass
void registerMyOtherClassForReflection(){
TypeInfo* metadata = &Mirror::metadata[Mirror::metadataIndex++];

metadata->name = "MyOtherClass";

metadata->pushProperty(Property("hello", offsetof(MyOtherClass, MyOtherClass::hello), Type::INT));
metadata->pushProperty(Property("world", offsetof(MyOtherClass, MyOtherClass::world), Type::INT));

}


// Reflection code for AnotherClassBitesTheDust
void registerAnotherClassBitesTheDustForReflection(){
TypeInfo* metadata = &Mirror::metadata[Mirror::metadataIndex++];

metadata->name = "AnotherClassBitesTheDust";

metadata->pushProperty(Property("queenType", offsetof(AnotherClassBitesTheDust, AnotherClassBitesTheDust::queenType), TypeDef(Type::CHAR, true)));
metadata->pushProperty(Property("isFredy", offsetof(AnotherClassBitesTheDust, AnotherClassBitesTheDust::isFredy), Type::BOOL));
metadata->pushProperty(Property("indexOfAwesomeness", offsetof(AnotherClassBitesTheDust, AnotherClassBitesTheDust::indexOfAwesomeness), Type::INT));

}

TypeInfo Mirror::metadata[];
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
}

void registerALLForReflection() {

registerMyClassForReflection();
registerMyStructureForReflection();
registerMyOtherClassForReflection();
registerAnotherClassBitesTheDustForReflection();

}