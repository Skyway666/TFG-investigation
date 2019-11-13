
#include "MyClass.h"


int main() {
	MyClass::registerForReflection();

	MyClass::metadata.cleanUp();
}