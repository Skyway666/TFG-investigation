#include "../../Mirror/TypeInfo.h"

TypeInfo Reflection::metadata[];
int Reflection::metadataIndex = 0;

Reflection::Reflection() {
}


Reflection::~Reflection() {
}


TypeInfo* Reflection::getMetadataFor(const char* objectName) {

	for (int i = 0; i < metadataIndex; i++)
		if (strcmp(objectName, metadata[i].name) == 0)
			return &metadata[i];

	return nullptr;
}