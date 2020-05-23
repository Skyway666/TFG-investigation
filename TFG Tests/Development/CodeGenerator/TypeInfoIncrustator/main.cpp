#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

// This program will produce a file with a variable initialized by a file
void main(int argc, char* args[]) {
	const char* input = args[1];
	const char* output = args[2];

	std::ifstream typeInfoFile(input);
	if (!typeInfoFile) {
		// Couldn't find Reflection.h
		return;
	}
	// Copy in new file


	// Create new file
	std::ofstream typeInfoIncFile(output, std::ofstream::binary);

	typeInfoIncFile << std::endl << std::endl;
	typeInfoIncFile << "const char* typeInfoCode = R\"(";

	std::string line;
	while (std::getline(typeInfoFile, line)) {
		// Output the text from the file
		typeInfoIncFile << line;
		typeInfoIncFile << "\n";
	}
	typeInfoIncFile << ")\";";

	// Cleanup
	typeInfoFile.close();
	typeInfoIncFile.close();

	return;
}