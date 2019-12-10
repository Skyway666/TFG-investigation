#ifndef MYCLASS_CLASS
#define MYCLASS_CLASS

#include "MyClass.generated.h"

class MyClass {
public:
	// Fields
	int a = 143;
	int b = 82;
	bool is = false;
	const char* name = "MyClass";
	char message[150] = "LOL";
	int numbers[3];


	// Methods
	int sum1ToA(bool sum) {
		if (sum)
			a += 1;

		return a;
	}


	// TODO(Lucas): Should be stored in a list. Outside of the class, with information to find it by string or template
	static TypeInfo metadata;
	static void registerForReflection();
};

#endif