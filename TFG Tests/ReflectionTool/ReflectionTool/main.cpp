
#include "MyClass.h"


int main() {

	MyClass::registerForReflection();

	MyClass instance;
	instance.a = 5;
	instance.b = -10;
	instance.is = true;
	instance.message = "I am being reflected now";



	int a_value = MyClass::metadata.getIntegerValue(&instance, "a");
	int b_value = MyClass::metadata.getIntegerValue(&instance, "b");
	bool is_value = MyClass::metadata.getBoolValue(&instance, "is");
	const char* message_value = MyClass::metadata.getStringValue(&instance, "message");

	return 0;

}