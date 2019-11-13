#ifndef TYPEINFO_CLASS
#define TYPEINFO_CLASS

#define MAX_PROPERTIES 30
// Static part from reflection library
enum Type {
	INT,
	STRING,
	BOOL
};

// TODO(Lucas): Consider changing name
struct Property {
	Property(const char* name, int offset, Type type):name(name), offset(offset), type(type) {}
	const char* name;
	size_t offset;
	Type type;
};

class TypeInfo {
public:

	TypeInfo() {
		for (int i = 0; i < MAX_PROPERTIES; i++)
			properties[i] = nullptr;
	}
	int getIntegerValue(void* ptr, const char* name) {

	}
	
	unsigned int property_index;
	Property* properties[MAX_PROPERTIES];

	void pushProperty(Property* property) {
		properties[property_index++] = property;
	}

	void cleanUp() {
		for (int i = 0; i < MAX_PROPERTIES; i++)
			if (properties[i]) delete properties[i];

	}

};


#endif //TYPEINFO_CLASS