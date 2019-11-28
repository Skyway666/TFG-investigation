#ifndef TYPEINFO_CLASS
#define TYPEINFO_CLASS

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
	BOOL
};

// TODO(Lucas): Consider changing name
struct Property {
	Property(){}
	Property(const char* name, int offset, Type type):name(name), offset(offset), type(type) {}
	const char* name = "null";
	size_t offset = 0;
	Type type = Type::NULL_TYPE;
};

struct Method {
	int argumentCount = 0;
	const char* name = "Null Method";
	Type returnValue = Type::NULL_TYPE;
	Type arguments[MAX_ARGUMENTS];
	void (*function_wrapper)(void);
};

// To be used  by the function wrapper (could be stored in a static structure)
// Metadata::Invoke() (metadata instance) will fill the arguments, execute the function wrapper, and return the appropiate return value
struct MethodDataHolder {
	int* integerReturn;
	void* instancePointer;
	
	int boolArgumentsCount = 0;
	bool boolArguments[10];
};

class TypeInfo {
public:

	// Properties
	unsigned int property_index = 0;
	Property properties[MAX_PROPERTIES];

	void pushProperty(Property property) {
		properties[property_index++] = property;
	}

	// Get field info from pointers
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


	// Methods
	unsigned int method_index = 0;
	Method methods[MAX_METHODS];
	MethodDataHolder methodDataHolder;

	void pushMethod(Method method) {
		methods[method_index++] = method;
	}
	// Invoke methods from pointers

	void PushIntReturnPointer(int* returnPointer) {
		methodDataHolder.integerReturn = returnPointer;
	}
	void PushBoolArgument(bool boolArgument) {
		methodDataHolder.boolArguments[methodDataHolder.boolArgumentsCount++] = boolArgument;
	}

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
		for (int i = 0; i < property_index; i++)
			if (strcmp(name, methods[i].name) == 0)
				return methods[i];

		return Method();
	}

};


#endif //TYPEINFO_CLASS