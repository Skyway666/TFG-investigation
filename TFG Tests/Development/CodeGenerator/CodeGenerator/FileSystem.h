#pragma once
#include <iostream>
#include <fstream>
#include <string>

// Itereate files
#include <filesystem>

// Initializes dynamic memory
int ImportFileString(const char* file_name, char** buffer) {
	std::ifstream file;
	file.open(file_name, std::fstream::out | std::fstream::binary);
	if (!file) {
		return 0;
	}
	
	std::string line;
	std::string text;
	while (std::getline(file, line)) {
		text += line;
		text += '\n';
	}
	int length = text.length();
	*buffer = new char[length + 1];
	strcpy_s(*buffer, length + 1, text.c_str());

	return text.length();
}

bool checkExtension(std::string file, std::string extension) {
	return	file.substr(file.find_last_of(".") + 1) == extension;
}