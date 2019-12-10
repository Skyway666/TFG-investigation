
#include "MyClass.h"


int main() {

	MyClass::registerForReflection();

	MyClass instance;
	instance.a = 5;
	instance.b = -10;
	instance.is = true;
	instance.name = "MyClass - Reflected";
	strcpy_s(instance.message, 150, "Hi, I'm a reflected dynamic message");
	instance.numbers[0] = 3;
	instance.numbers[1] = -4;
	instance.numbers[2] = 9;



	int a_value = MyClass::metadata.getIntegerValue(&instance, "a");
	int b_value = MyClass::metadata.getIntegerValue(&instance, "b");
	bool is_value = MyClass::metadata.getBoolValue(&instance, "is");
	const char* name_value = MyClass::metadata.getConstStringValue(&instance, "name");
	char message_value[150];
	MyClass::metadata.getStringVaue(&instance, "message", message_value, 150);
	int numbers_value[3];
	MyClass::metadata.getArrayValue(&instance, "numbers", numbers_value);

	Type a_type = MyClass::metadata.getFieldType("a");
	Type is_type = MyClass::metadata.getFieldType("is");
	Type name_type = MyClass::metadata.getFieldType("name");
	Type message_type = MyClass::metadata.getFieldType("message");
	Type numbers_type = MyClass::metadata.getFieldType("numbers");


	// Methods
	int sum1toA_return = 0;

	MyClass::metadata.methodDataHolder.PushIntReturnPointer(&sum1toA_return);
	MyClass::metadata.methodDataHolder.PushBoolArgument(true);
	MyClass::metadata.Invoke(&instance, "sum1ToA");

	return 0;

}