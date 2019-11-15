
#include "MyClass.h"


int main() {

	MyClass::registerForReflection();

	MyClass instance;
	instance.a = 5;
	instance.b = -10;
	instance.is = true;



	int a_value = MyClass::metadata.getIntegerValue(&instance, "a");
	int b_value = MyClass::metadata.getIntegerValue(&instance, "b");
	bool is_value = MyClass::metadata.getBoolValue(&instance, "is");

	return 0;

}