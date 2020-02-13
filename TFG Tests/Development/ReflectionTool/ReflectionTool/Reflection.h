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
	INT,
	CONST_STRING,
	STRING,
	BOOL,
	ARRAY
};

// TODO(Lucas): Consider changing name
struct Property {
	Property() {}
	Property(const char* name, int offset, Type type) :name(name), offset(offset), type(type) {}
	const char* name = "null";
	size_t offset = 0;
	Type type = Type::NULL_TYPE;

	// Only to be used for arrays
	Type arrayType = Type::NULL_TYPE;
	int arraySize = 0; // IN MEMORY. To get size of elements -> arraySize / enum2sizeof(arrayType)
};

struct Method {
	// Not used by reflection system "Invoke"
	int argumentCount = 0;
	Type returnValue = Type::NULL_TYPE;
	Type arguments[MAX_ARGUMENTS];

	// Only really needed by now
	const char* name = "Null Method";
	void(*function_wrapper)(void);
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
	unsigned int property_index = 0;
	Property properties[MAX_PROPERTIES];

	void pushProperty(Property property) {
		properties[property_index++] = property;
	}

	// Get field data from pointers
	int getIntegerValue(void* instance_ptr, const char* name) {
		Property property = getPropertyByStringAndType(name, Type::INT);

		int ret = *((int*)((size_t)instance_ptr + property.offset));

		return ret;
	}

	bool getBoolValue(void* instance_ptr, const char* name) {
		Property property = getPropertyByStringAndType(name, Type::BOOL);

		bool ret = *((bool*)((size_t)instance_ptr + property.offset));

		return ret;
	}
	const char* getConstStringValue(void* instance_ptr, const char* name) {
		Property property = getPropertyByStringAndType(name, Type::CONST_STRING);

		const char* ret = *((const char**)((size_t)instance_ptr + property.offset));

		return ret;
	}

	void getStringVaue(void* instance_ptr, const char* name, char* output_string, size_t size) {
		Property property = getPropertyByStringAndType(name, Type::STRING);

		char* to_copy_str = ((char*)((size_t)instance_ptr + property.offset));

		strcpy_s(output_string, size, to_copy_str);
	}

	void getArrayValue(void* instance_ptr, const char* name, void* output_array) {
		Property property = getPropertyByStringAndType(name, Type::ARRAY);

		void* to_copy_arr = ((void*)((size_t)instance_ptr + property.offset));

		memcpy(output_array, to_copy_arr, property.arraySize);
	}

	// Should return some form of container, since several variables of different type can be declared with the same variable name
	Type getFieldType(const char* name) {
		for (int i = 0; i < property_index; i++)
			if (strcmp(name, properties[i].name) == 0)
				return properties[i].type;

		return Type::NULL_TYPE;
	}


	// Methods
	unsigned int method_index = 0;
	Method methods[MAX_METHODS];
	MethodDataHolder methodDataHolder;

	void pushMethod(Method method) {
		methods[method_index++] = method;
	}
	// Invoke methods from pointers

	void Invoke(void* instance_ptr, const char* name) {
		Method method = getMethodByString(name);
		methodDataHolder.instancePointer = instance_ptr;

		method.function_wrapper();
	}
	// Helper functions

	Property getPropertyByStringAndType(const char* name, Type type) {
		for (int i = 0; i < property_index; i++)
			if (strcmp(name, properties[i].name) == 0 && type == properties[i].type)
				return properties[i];

		return Property();
	}

	// Should be string, return value and arguments
	Method getMethodByString(const char* name) {
		for (int i = 0; i < method_index; i++)
			if (strcmp(name, methods[i].name) == 0)
				return methods[i];

		return Method();
	}

};

class Reflection {
public:
	Reflection();
	~Reflection();


	static TypeInfo* getMetadataFor(const char* objectName);

	static int metadata_index;
	static TypeInfo metadata[MAX_TYPE_INFO];
};
