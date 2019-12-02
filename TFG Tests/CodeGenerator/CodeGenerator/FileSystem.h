#pragma once
#include <iostream>
#include <fstream>

// Initializes dynamic memory
char* ImportFileString(const char* file_name) {
	std::ifstream file;
	file.open(file_name, std::fstream::out | std::fstream::binary);
	if (!file) {
		return nullptr;
	}
	// get length of file:
	file.seekg(0, file.end);
	int size = file.tellg();
	file.seekg(0, file.beg);

	char* ret = new char[size];
	file.read(ret, size);

	return ret;
}