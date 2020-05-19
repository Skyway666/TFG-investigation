#pragma once
#include <iostream>
#include <fstream>

// Itereate files
#include <filesystem>

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

bool checkExtension(std::string file, std::string extension) {
	return	file.substr(file.find_last_of(".") + 1) == extension;
}