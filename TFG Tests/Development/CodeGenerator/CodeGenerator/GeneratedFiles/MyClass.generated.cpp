#include "Reflection.h"
#include "MyClass.generated.h"

void registerMyClassForReflection(){
TypeInfo* metadata = &Reflection::metadata[Reflection::metadataIndex++];

metadata->name = MyClass

metadata->pushProperty(Property("a", offsetof(MyClass, MyClass::a), Type::INT));
metadata->pushProperty(Property("b", offsetof(MyClass, MyClass::b), Type::INT));
metadata->pushProperty(Property("is", offsetof(MyClass, MyClass::is), Type::BOOL));
metadata->pushProperty(Property("name", offsetof(MyClass, MyClass::name), Type::CONST_STRING));
metadata->pushProperty(Property("message", offsetof(MyClass, MyClass::message), Type::STRING, 150 * sizeof(char)));
}
