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

