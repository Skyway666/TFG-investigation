#ifndef REFLECTION
#define REFLECTION



// Register function for MyClass
void registerMyClassForReflection();



// Register function for MyOtherClass
void registerMyOtherClassForReflection();



// Register function for YetAnotherClass
void registerYetAnotherClassForReflection();



// Global register function
void registerALLForReflection() {

registerMyClassForReflection();
registerMyOtherClassForReflection();
registerYetAnotherClassForReflection();

}

#endif //REFLECTION