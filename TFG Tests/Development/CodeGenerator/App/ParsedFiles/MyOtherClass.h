#ifndef MYCLASS_CLASS
#define MYCLASS_CLASS


class MyOtherClass {
public:
	// Fields
	int hello = 143;
	int world = 82;
};

class YetAnotherClass {
	public:
		bool isActive;
		char test;
		MyOtherClass* child;

		bool getActive(int index);
};

#endif