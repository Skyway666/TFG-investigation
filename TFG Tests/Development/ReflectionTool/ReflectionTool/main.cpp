
#include "MyClass.h"
#include "Reflection.h"


#include "MyClass.generated.h"


int main() {

	registerMyClassForReflection();


	MyClass instance;
	instance.a = 5;
	instance.b = -10;
	instance.is = true;
	instance.name = "MyClass - Reflected";
	strcpy_s(instance.message, 150, "Hi, I'm a reflected dynamic message");
	instance.numbers[0] = 3;
	instance.numbers[1] = -4;
	instance.numbers[2] = 9;


	TypeInfo* myClassMetadata = Reflection::getMetadataFor("MyClass");

	int a_value = myClassMetadata->getIntegerValue(&instance, "a");
	int b_value = myClassMetadata->getIntegerValue(&instance, "b");
	bool is_value = myClassMetadata->getBoolValue(&instance, "is");
	const char* name_value = myClassMetadata->getConstStringValue(&instance, "name");
	char message_value[150];
	myClassMetadata->getStringVaue(&instance, "message", message_value, 150);
	int numbers_value[3];
	myClassMetadata->getArrayValue(&instance, "numbers", Type::INT, numbers_value);

	TypeDef a_type = myClassMetadata->getFieldType("a");
	TypeDef is_type = myClassMetadata->getFieldType("is");
	TypeDef name_type = myClassMetadata->getFieldType("name");
	TypeDef message_type = myClassMetadata->getFieldType("message");
	TypeDef numbers_type = myClassMetadata->getFieldType("numbers");


	// Methods

	// void sum1toA(bool)
	int sum1toA_return = 0;
	bool boolArgument1 = true;

	myClassMetadata->methodDataHolder.PushReturnPointer(&sum1toA_return);
	myClassMetadata->methodDataHolder.PushArgument(&boolArgument1);
	myClassMetadata->Invoke(&instance, "sum1ToA");

	myClassMetadata->methodDataHolder.clear();

	// int addNumbers(int, int)

	// Data
	int addNumbers_return = 0;
	int intArgument1 = 3;
	int intArgument2 = 10;

	// Method definition, for overload support
	MethodDef def;
	def.argumentCount = 2;
	def.arguments[0] = Type::INT;
	def.arguments[1] = Type::INT;
	def.name = "addNumbers";

	myClassMetadata->methodDataHolder.PushReturnPointer(&addNumbers_return);
	myClassMetadata->methodDataHolder.PushArgument(&intArgument1);
	myClassMetadata->methodDataHolder.PushArgument(&intArgument2);
	myClassMetadata->Invoke(&instance, def);

	myClassMetadata->methodDataHolder.clear();
	def.clear();

	// int addNumbers(int, int, int)
	intArgument1 = 4;
	intArgument2 = 8;
	int intArgument3 = 2;

	// Method definition, for overload support
	def.argumentCount = 3;
	def.arguments[0] = Type::INT;
	def.arguments[1] = Type::INT;
	def.arguments[2] = Type::INT;
	def.name = "addNumbers";
	
	myClassMetadata->methodDataHolder.PushReturnPointer(&addNumbers_return);
	myClassMetadata->methodDataHolder.PushArgument(&intArgument1);
	myClassMetadata->methodDataHolder.PushArgument(&intArgument2);
	myClassMetadata->methodDataHolder.PushArgument(&intArgument3);
	myClassMetadata->Invoke(&instance, def);
	

	return 0;

}