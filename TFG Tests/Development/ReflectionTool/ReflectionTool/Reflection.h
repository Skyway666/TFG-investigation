#pragma once
#define MAX_TYPE_INFO 100

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
	CONST_STRING,
	STRING,
	BOOL
};

// TODO(Lucas): Consider changing name

// Struc intended to be returned to the user
struct TypeDef {
	TypeDef(){}
	TypeDef(Type type, int arraySize): type(type), arraySize(arraySize){}

	Type type = Type::NULL_TYPE;
	int arraySize = -1;
};

// Private stuff, don't give the user access
struct Property {
	Property() {}
	Property(const char* name, int offset, Type type) :name(name), offset(offset), type(type) {}
	Property(const char* name, int offset, Type type, int arraySize) :
	name(name), offset(offset), type(type), arraySize(arraySize) {}
	const char* name = "null";
	size_t offset = 0;
	Type type = Type::NULL_TYPE;

	// Only to be used for arrays
	int arraySize = 0; // IN MEMORY. To get size of elements -> arraySize / enum2sizeof(type). If arraySize is more than 0, it is an array
};

struct MethodDef {

	int argumentCount = 0;
	Type returnValue = Type::NULL_TYPE;
	Type arguments[MAX_ARGUMENTS] = {Type::NULL_TYPE};
	const char* name = "Null Method";

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
		returnValue = Type::NULL_TYPE;
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


	int argumentsCount = 0;
	void* argumentsPointers[MAX_ARGUMENTS];

	// Public to user
	void PushReturnPointer(void* userPointer) {
		returnPointer = userPointer;
	}
	void PushArgument(void* argument) {
		argumentsPointers[argumentsCount++] = argument;
	}

	void clear() {
		returnPointer = nullptr;
		instancePointer = nullptr;
		argumentsCount = 0;
		for (int i = 0; i < MAX_ARGUMENTS; i++) {
			argumentsPointers[i] = nullptr;
		}
	}
};

class TypeInfo {
public:

	const char* name;
	// Properties
	unsigned int propertyIndex = 0;
	Property properties[MAX_PROPERTIES];

	void pushProperty(Property property) {
		properties[propertyIndex++] = property;
	}

	// Get field data from pointers
	int getIntegerValue(void* instance_ptr, const char* name) {
		Property property = getVariable(name, Type::INT);

		int ret = *((int*)((size_t)instance_ptr + property.offset));

		return ret;
	}

	bool getBoolValue(void* instance_ptr, const char* name) {
		Property property = getVariable(name, Type::BOOL);

		bool ret = *((bool*)((size_t)instance_ptr + property.offset));

		return ret;
	}
	const char* getConstStringValue(void* instance_ptr, const char* name) {
		Property property = getVariable(name, Type::CONST_STRING);

		const char* ret = *((const char**)((size_t)instance_ptr + property.offset));

		return ret;
	}

	void getStringVaue(void* instance_ptr, const char* name, char* output_string, size_t size) {
		Property property = getVariable(name, Type::STRING);

		char* to_copy_str = ((char*)((size_t)instance_ptr + property.offset));

		strcpy_s(output_string, size, to_copy_str);
	}

	void getArrayValue(void* instance_ptr, const char* name, Type elementType, void* output_array) {
		Property property = getArray(name, elementType);

		void* to_copy_arr = ((void*)((size_t)instance_ptr + property.offset));

		memcpy(output_array, to_copy_arr, property.arraySize);
	}

	// Should return some form of container, since several variables of different type can be declared with the same variable name
	TypeDef getFieldType(const char* name) {
		for (int i = 0; i < propertyIndex; i++)
			if (strcmp(name, properties[i].name) == 0) {
				return TypeDef(properties[i].type, properties[i].arraySize);
			}
		
		return TypeDef();
	}


	// Methods
	unsigned int methodIndex = 0;
	Method methods[MAX_METHODS];
	MethodDataHolder methodDataHolder;

	void pushMethod(Method method) {
		methods[methodIndex++] = method;
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


	// Get Properties
	Property getVariable(const char* name, Type type) {
		for (int i = 0; i < propertyIndex; i++)
			if (strcmp(name, properties[i].name) == 0 && type == properties[i].type && properties[i].arraySize == 0)
				return properties[i];

		return Property();
	}

	Property getArray(const char* name, Type type) {
		for (int i = 0; i < propertyIndex; i++)
			if (strcmp(name, properties[i].name) == 0 && type == properties[i].type && properties[i].arraySize != 0)
				return properties[i];

		return Property();
	}

	// Get methods
	Method getMethodByString(const char* name) {
		for (int i = 0; i < methodIndex; i++)
			if (strcmp(name, methods[i].def.name) == 0)
				return methods[i];

		return Method();
	}

	Method getMethodByDef(MethodDef def) {
		for (int i = 0; i < methodIndex; i++)
			if (methods[i].def == def)
				return methods[i];

		return Method();
	}

};

class Reflection {
public:
	Reflection();
	~Reflection();


	static TypeInfo* getMetadataFor(const char* objectName);

	static int metadataIndex;
	static TypeInfo metadata[MAX_TYPE_INFO];
};

