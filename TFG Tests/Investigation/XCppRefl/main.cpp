

#include <iostream>
#include <stdlib.h>
#include <assert.h>

#include "A.hpp"
#include "A_reflection.hpp"
#include "reflcpp/ClassType_tmpl.hpp"
#include "reflcpp/BoundClassType_tmpl.hpp"
#include "reflcpp/Exceptions.hpp"


using namespace std;
using namespace reflcpp;

int main() {

	// Instance and declaration
	A A_instance;
	A_instance.f1 = 4;

	// Reflection
	ClassType A_c = ClassType::getClass("A");
	DataMember f1_dm = A_c.getDataMember("f1");
	int f1_value = f1_dm.ref<int>(&A_instance);

	auto data_members = A_c.getDataMembers();

	printf_s("Hello World, my reflected class is named %s, the value of 'f1' in my instance is %i\n\n", A_c.name().c_str(), f1_value);

	printf_s("The attributes on the %s class are:\n", A_c.name().c_str());
	for (auto data_member : data_members) {
		printf_s("   - %s %s\n", data_member.typeName().c_str(), data_member.name().c_str());
	}

	return 0;
}