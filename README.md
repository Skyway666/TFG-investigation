### Mirror

Mirror is a tool which generates a custom reflection system for your C++ code.

## How to use it

1- Fill the config file with the following information:
	- input-directory: Directory which the tool will iterate looking for .h files to generate reflection
	- output-directory: Directory where the generated files will be placed (Reflection.h and Reflection.cpp)
	- reflected-objects: Name of the objects which the tool needs to generate reflection for

2- Place your header files within the "input-directory"

3- Execute the Mirror.exe

4- Include Reflection.h and Reflection.cpp to your project

5- Enjoy reflection capabilities in C++!

## Example

This build, upon download, features an already functional config file and some example headers for the tool to work.
Feel free to execute the tool and notice how the before empty "GeneratedFiles" folder, is now filled with the reflection
code needed to reflect the example headers.


Author: https://github.com/Skyway666