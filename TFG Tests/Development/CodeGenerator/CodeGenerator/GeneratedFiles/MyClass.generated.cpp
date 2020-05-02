#include "Reflection.h"
#include "MyClass.generated.h"

void MyClassFuncWrap_sum1ToA_BOOL() {
TypeInfo* metadata = Reflection::getMetadataFor("MyClass");
MethodDataHolder mdh = metadata->methodDataHolder;

*(int*)mdh.returnPointer = ((MyClass*)mdh.instancePointer)->sum1ToA(*(bool*)mdh.argumentPointers[0]);
}

void MyClassFuncWrap_addNumbers_INT_INT() {
TypeInfo* metadata = Reflection::getMetadataFor("MyClass");
MethodDataHolder mdh = metadata->methodDataHolder;

*(int*)mdh.returnPointer = ((MyClass*)mdh.instancePointer)->addNumbers(*(int*)mdh.argumentPointers[0], *(int*)mdh.argumentPointers[1]);
}

void MyClassFuncWrap_addNumbers_INT_INT_INT() {
TypeInfo* metadata = Reflection::getMetadataFor("MyClass");
MethodDataHolder mdh = metadata->methodDataHolder;

*(int*)mdh.returnPointer = ((MyClass*)mdh.instancePointer)->addNumbers(*(int*)mdh.argumentPointers[0], *(int*)mdh.argumentPointers[1], *(int*)mdh.argumentPointers[2]);
}

void registerMyClassForReflection(){
TypeInfo* metadata = &Reflection::metadata[Reflection::metadataIndex++];

metadata->name = MyClass

metadata->pushProperty(Property("a", offsetof(MyClass, MyClass::a), Type::INT));
metadata->pushProperty(Property("b", offsetof(MyClass, MyClass::b), Type::INT));
metadata->pushProperty(Property("is", offsetof(MyClass, MyClass::is), Type::BOOL));
metadata->pushProperty(Property("name", offsetof(MyClass, MyClass::name), TypeDef(Type::CHAR, true)));
metadata->pushProperty(Property("message", offsetof(MyClass, MyClass::message), TypeDef(Type::CHAR, 150 * (int)sizeof(char))));
metadata->pushProperty(Property("numbers", offsetof(MyClass, MyClass::numbers), TypeDef(Type::INT, 3 * (int)sizeof(int))));
metadata->pushProperty(Property("child", offsetof(MyClass, MyClass::child), TypeDef(Type::OBJECT, "MyOtherClass")));
metadata->pushProperty(Property("childPointer", offsetof(MyClass, MyClass::childPointer), TypeDef(Type::OBJECT, "MyOtherClass", true)));
metadata->pushProperty(Property("numberPointer", offsetof(MyClass, MyClass::numberPointer), TypeDef(Type::INT, true)));

Method method;
method.function_wrapper = &MyClassFuncWrap_sum1ToA_BOOL;
method.def.name = "sum1ToA";
method.def.returnValue = Type::INT;
method.def.pushArgument(Type::BOOL);

metadata->pushMethod(method);
method.def.clear()

method.function_wrapper = &MyClassFuncWrap_addNumbers_INT_INT;
method.def.name = "addNumbers";
method.def.returnValue = Type::INT;
method.def.pushArgument(Type::INT);
method.def.pushArgument(Type::INT);

metadata->pushMethod(method);
method.def.clear()

method.function_wrapper = &MyClassFuncWrap_addNumbers_INT_INT_INT;
method.def.name = "addNumbers";
method.def.returnValue = Type::INT;
method.def.pushArgument(Type::INT);
method.def.pushArgument(Type::INT);
method.def.pushArgument(Type::INT);

metadata->pushMethod(method);
method.def.clear()

}
