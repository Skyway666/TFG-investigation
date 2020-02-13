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


	// Methods
	int sum1ToA(bool sum) {
		if (sum)
			a += 1;

		return a;
	}
};

#endif