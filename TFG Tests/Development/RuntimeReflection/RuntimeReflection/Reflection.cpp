#include "../../Mirror/TypeInfo.h"

TypeInfo Mirror::metadata[];
int Mirror::metadataIndex = 0;

Mirror::Mirror() {
}


Mirror::~Mirror() {
}


TypeInfo* Mirror::getMetadataFor(const char* objectName) {

	for (int i = 0; i < metadataIndex; i++)
		if (strcmp(objectName, metadata[i].name) == 0)
			return &metadata[i];

	return nullptr;
}