// MyClass.generated.h

#ifndef TYPEINFO_CLASS
#define TYPEINFO_CLASS

struct Property
{
    const char *name;
    size_t offset;
    int type;
}

class TypeInfo{
    int getIntValue(void *ptr, const char *propertyName);


    Property properties[MAX_PROPERTIES];
};
#endif




// -------------------------------------------------
// MyClass.h

#include "MyClass.generated.h"

class MyClass
{
public:

int fieldA;
int fieldB;

    static void registerForReflection();
    static int getIntFiledValue(MyClass* instance, const char* name);
    static TypeInfo myTypeInfo;
};

// -------------------------------------------------
// MyClass.cpp

// Internals of your class

// -------------------------------------------------
// MyClass.generated.cpp

void MyClass::registerForReflection()
{

}

int MyClass::getIntFiledValue(MyClass* instance, const char* name)
{
    myTypeInfo.getInt(instance, name);
}

// -------------------------------------------------
// main.cpp

#include "MyClass.h"

int main()
{
    MyClass::registerForReflection();


	MyClass c;
    int a = MyClass::getIntFiledValue(&c, "fieldA");
    int a = MyClass::myTypeInfo.getIntValue(&c, "fieldA"):
}
