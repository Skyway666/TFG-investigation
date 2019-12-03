
// Reflection is a singleton, which among others contains a list of Metadata.

int main() {

	// The code in "init()" is generated automatically. It fills a list of metadata with the name of the classes and pointers to functions that registers them.
	Reflection::init();

	
	// Executing code which registers "MyClass". 
		// Option 1
		Reflection::registerForReflection("MyClass");

		// Option 2
		Reflection::registerForReflection<MyClass>();

		// Option 3?
		Reflection::registerForReflection(MyClass);

	// Getting the "MyClass" metadata instance
		// Option 1
		Metadata* metadata = Reflection::getMetadata("MyClass");

		// Option 2
		metadata = Reflection::getMetadata<MyClass>();

		// Option 3?
		metadata = Reflection::getMetadata(MyClass);



}