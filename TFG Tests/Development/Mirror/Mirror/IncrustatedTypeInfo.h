

const char* typeInfoCode = R"(#define MAX_TYPE_INFO 100
#define MAX_PROPERTIES 30
#define MAX_METHODS 30
#define MAX_ARGUMENTS 10

// TODO(Lucas): Should be removed
#include<string>


// Static part from reflection library
enum Type {
	NULL_TYPE,
	VOID,
	INT,
	CHAR,
	BOOL,
	OBJECT // Struct or class
};


// Struc intended to be returned to the user
struct TypeDef {
	TypeDef(){}
	TypeDef(Type type): type(type){} // Basic variable
	TypeDef(Type type, int arraySize): type(type), arraySize(arraySize){} // Array of basic variables
	TypeDef(Type type, bool isPointer): type(type), isPointer(isPointer){} // Basic variable pointer
	TypeDef(Type type, int arraySize, bool isPointer): type(type), arraySize(arraySize), isPointer(isPointer){} // Array of basic variable pointers

	TypeDef(Type type, const char* objectName): type(type), objectName(objectName){} // Basic object
	TypeDef(Type type, const char* objectName, int arraySize) : type(type), objectName(objectName), arraySize(arraySize) {} // Array of basic objects
	TypeDef(Type type, const char* objectName, bool isPointer) : type(type), objectName(objectName), isPointer(isPointer) {} // Object pointer
	TypeDef(Type type, const char* objectName, int arraySize, bool isPointer) : type(type), objectName(objectName), arraySize(arraySize), isPointer(isPointer) {} //  Array of object pointers


	Type type = Type::NULL_TYPE;
	int arraySize = -1; // IN MEMORY. To get size of elements -> arraySize / enum2sizeof(type). If arraySize is different from -1, it is an array
	bool isPointer = false;
	const char* objectName = nullptr; // If the variable is of type Object, this will contain its name

	bool operator==(TypeDef typeDef) {
		bool objectNameCheck = false;
		if (objectName && typeDef.objectName) {
			// Both are initialized, names need to be compared
			objectNameCheck = strcmp(objectName, typeDef.objectName) == 0;
		}
		else if(!objectName && !typeDef.objectName){
			// Both are uninitialized, check is passed
			objectNameCheck = true;
		}
		// One is initialized and the other is not, check is not passed

		return type == typeDef.type &&
			arraySize == typeDef.arraySize &&
			isPointer == typeDef.isPointer &&
			objectNameCheck;
	}

	bool isArrayOf(TypeDef typeDef) {
		bool objectNameCheck = false;
		if (objectName && typeDef.objectName) {
			// Both are initialized, names need to be compared
			objectNameCheck = strcmp(objectName, typeDef.objectName) == 0;
		}
		else if (!objectName && !typeDef.objectName) {
			// Both are uninitialized, check is passed
			objectNameCheck = true;
		}
		// One is initialized and the other is not, check is not passed

		return type == typeDef.type &&
			isPointer == typeDef.isPointer &&
			arraySize != -1 &&
			objectNameCheck;
	}
};

// Private stuff, don't give the user access
struct Property {
	Property() {}
	Property(const char* name, int offset, TypeDef type) :name(name), offset(offset), type(type) {}
	const char* name = "null";
	size_t offset = 0;
	TypeDef type;
};

struct MethodDef {

	int argumentCount = 0;
	Type returnType = Type::NULL_TYPE;
	Type arguments[MAX_ARGUMENTS] = {Type::NULL_TYPE};
	const char* name = "Null Method";

	void pushArgument(Type argumentType) {
		arguments[argumentCount++] = argumentType;
	}

	bool operator==(MethodDef def) {

		if (strcmp(name, def.name) != 0)
			return false;

		if (argumentCount != def.argumentCount)
			return false;

		for (int i = 0; i < MAX_ARGUMENTS; i++) {
			if (arguments[i] != def.arguments[i]) {
				return false;
			}
		}

		return  true;	 
	}

	void clear() {
		argumentCount = 0;
		returnType = Type::NULL_TYPE;
		for (int i = 0; i < MAX_ARGUMENTS; i++)
			arguments[i] = Type::NULL_TYPE;
		name = "Null Method";
	}
};

struct Method {
	// Method definition
	MethodDef def;

	void(*function_wrapper)(void) = nullptr;

	void clear() {
		def.clear();
		function_wrapper = nullptr;
	}
};

// To be used  by the function wrapper (could be stored in a static structure)
// Metadata::Invoke() (metadata instance) will fill the arguments, execute the function wrapper, and return the appropiate return value
struct MethodDataHolder {
	// Private to user
	// Pointer where the function will be called
	void* instancePointer;
	// Return value
	void* returnPointer;


	int argumentPointerCount = 0;
	void* argumentPointers[MAX_ARGUMENTS];

	// Public to user
	void PushReturnPointer(void* userPointer) {
		returnPointer = userPointer;
	}
	void PushArgument(void* argument) {
		argumentPointers[argumentPointerCount++] = argument;
	}

	void clear() {
		returnPointer = nullptr;
		instancePointer = nullptr;
		argumentPointerCount = 0;
		for (int i = 0; i < MAX_ARGUMENTS; i++) {
			argumentPointers[i] = nullptr;
		}
	}
};

class TypeInfo {
public:

	const char* name;
	// Properties
	unsigned int propertyCount = 0;
	Property properties[MAX_PROPERTIES];

	void pushProperty(Property property) {
		properties[propertyCount++] = property;
	}

	// Get field data from pointers
	int getIntegerValue(void* instance_ptr, const char* name) {
		return *((int*)(getPropertyPointer(instance_ptr, name)));
	}

	bool getBoolValue(void* instance_ptr, const char* name) {
		return *((bool*)(getPropertyPointer(instance_ptr, name)));
	}
	char getCharValue(void* instance_ptr, const char* name) {
		return *((char*)(getPropertyPointer(instance_ptr, name)));
	}

	char* getStringVaue(void* instance_ptr, const char* name) {
		return *((char**)(getPropertyPointer(instance_ptr, name)));
	}

	void getArrayValue(void* instance_ptr, const char* name, void* output_array) {
		Property array = getProperty(name);
		void* to_copy_arr = ((void*)((size_t)instance_ptr + array.offset));
		memcpy(output_array, to_copy_arr, array.type.arraySize);
	}

	void* getPointerValue(void* instance_ptr, const char* name) {
		return *((void**)(getPropertyPointer(instance_ptr, name)));
	}

	void* getPropertyPointer(void* instance_ptr, const char* name) {
		Property object = getProperty(name);
		return ((void*)((size_t)instance_ptr + object.offset));
	}
	
	// Get property types
	TypeDef getPropertyType(const char* name) {
		for (int i = 0; i < propertyCount; i++)
			if (strcmp(name, properties[i].name) == 0) {
				return properties[i].type;
			}
		
		return TypeDef();
	}

	// Get Properties
	Property getProperty(const char* name) {
		for (int i = 0; i < propertyCount; i++)
			if (strcmp(name, properties[i].name) == 0)
				return properties[i];

		return Property();
	}


	// Methods
	unsigned int methodCount= 0;
	Method methods[MAX_METHODS];
	MethodDataHolder methodDataHolder;

	void pushMethod(Method method) {
		methods[methodCount++] = method;
	}
	// Invoke methods from pointers
	void Invoke(void* instance_ptr, const char* name) {
		Method method = getMethodByString(name);
		methodDataHolder.instancePointer = instance_ptr;

		method.function_wrapper();
	}

	void Invoke(void* instance_ptr, MethodDef def) {
		Method method = getMethodByDef(def);
		methodDataHolder.instancePointer = instance_ptr;

		method.function_wrapper();
	}

	// Get methods
	Method getMethodByString(const char* name) {
		for (int i = 0; i < methodCount; i++)
			if (strcmp(name, methods[i].def.name) == 0)
				return methods[i];

		return Method();
	}

	Method getMethodByDef(MethodDef def) {
		for (int i = 0; i < methodCount; i++)
			if (methods[i].def == def)
				return methods[i];

		return Method();
	}

};

class Mirror {
public:
	Mirror();
	~Mirror();


	static TypeInfo* getMetadataFor(const char* objectName);

	static int metadataIndex;
	static TypeInfo metadata[MAX_TYPE_INFO];
};

)";