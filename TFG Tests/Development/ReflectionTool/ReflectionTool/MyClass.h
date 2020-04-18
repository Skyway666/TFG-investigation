#ifndef MYCLASS_CLASS
#define MYCLASS_CLASS

class MyOtherClass {
	bool silly = true;
	int hi = 10;
};
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
	int* numberPointer = nullptr;


	// Methods
	int sum1ToA(bool sum) {
		if (sum)
			a += 1;

		return a;
	}

	int addNumbers(int a, int b){
		return a + b;
	}
	int addNumbers(int& a, int b, int c) {
		a = b + c;
		return a + b + c;
	}
};

#endif