#include "Reflection.h"

TypeInfo Reflection::metadata[];
int Reflection::metadata_index = 0;

Reflection::Reflection() {
}


Reflection::~Reflection() {
}


TypeInfo* Reflection::getMetadataFor(const char* objectName) {

	for (int i = 0; i < metadata_index; i++)
		if (strcmp(objectName, metadata[i].name) == 0)
			return &metadata[i];

	return nullptr;
}