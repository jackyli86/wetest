#include "stdafx.h"

#include "class_construct.h"

class_construct get_default_class() {
	return class_construct();
}

TEST(TEST_CLASS, TEST_CLASS_CONSTRUCT) {
	class_construct a;

	class_construct b = a;

	class_construct c(std::move(get_default_class()));
	cout << "num = " << c.get_num() << endl;
	auto i = 0;
	while(i++ < 100000){}
}