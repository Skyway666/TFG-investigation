#ifndef MYCLASS_CLASS
#define MYCLASS_CLASS


class MyClass {
public:
	// Fields
	int a = 143;
	int b = 82;
	bool is = false;
	const char* name = "MyClass";
	char message[150] = "LOL";
	int numbers[3];
	MyOtherClass child;
	MyOtherClass* childPointer;
	int* numberPointer;
	bool* booleanPointers[5];
	MyOtherClass classes[21];
	MyOtherClass* classArrays[34];



	// Methods
	int sum1ToA(bool sum);
	int addNumbers(int a, int b);
	int addNumbers(int a, int b, int c);
	int reference(bool &hello);
	char* getName(bool* localizationCheck);
	MyClass returnSomething(MyOtherClass* jaja)
};

#endif