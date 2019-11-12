#ifndef TYPEINFO_CLASS
#define TYPEINFO_CLASS

#include<vector>

// Static part from reflection library
enum Type {
	INT,
	STRING,
	BOOL
};

struct StringWithLength {
	char* string;
	unsigned int length;
};

struct Property {
	Property(StringWithLength str_len, int offset, Type type):offset(offset), type(type) {
		name = new char[str_len.length];
		memcpy((void*)name, str_len.string, str_len.length);
	}
	~Property() {
		delete name;
	}
	const char* name;
	size_t offset;
	Type type;
};

class TypeInfo {
public:
	int getIntegerValue(void* ptr, const char* name) {

	}
	// Maybe use an array
	std::vector<Property> properties;

};


#endif //TYPEINFO_CLASS