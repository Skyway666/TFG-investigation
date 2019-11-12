#ifndef MYCLASS_CLASS
#define MYCLASS_CLASS

#include "MyClass.generated.h"

class MyClass {
public:
	int a;
	int b;


	// Should be stored in a list. Outside of the class, with information to find it by string or template
	static TypeInfo metadata;
	static void registerForReflection();
};

#endif