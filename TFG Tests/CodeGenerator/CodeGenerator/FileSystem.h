#pragma once
#include <iostream>
#include <fstream>

// Initializes dynamic memory
int ImportFileString(const char* file_name, char** buffer) {
	std::ifstream file;
	file.open(file_name, std::fstream::out | std::fstream::binary);
	if (!file) {
		return 0;
	}
	// get length of file:
	file.seekg(0, file.end);
	int size = file.tellg();
	file.seekg(0, file.beg);

	*buffer = new char[size];
	file.read(*buffer, size);

	return size;
}