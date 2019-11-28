
#include "MyClass.h"


int main() {

	MyClass::registerForReflection();

	MyClass instance;
	instance.a = 5;
	instance.b = -10;
	instance.is = true;
	instance.name = "MyClass - Reflected";
	strcpy_s(instance.message, 150, "Hi, I'm a reflected dynamic message");



	int a_value = MyClass::metadata.getIntegerValue(&instance, "a");
	int b_value = MyClass::metadata.getIntegerValue(&instance, "b");
	bool is_value = MyClass::metadata.getBoolValue(&instance, "is");
	const char* name_value = MyClass::metadata.getConstStringValue(&instance, "name");
	char message_value[150];
	MyClass::metadata.getStringVaue(&instance, "message", message_value, 150);

	int sum1toA_return = 0;

	MyClass::metadata.PushIntReturnPointer(&sum1toA_return);
	MyClass::metadata.PushBoolArgument(true);
	MyClass::metadata.Invoke(&instance, "sum1ToA");

	return 0;

}