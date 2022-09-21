#pragma once
#include "stdafx.h"

#include "class_stream.h"

TEST(TEST_CLASS, TEST_CLASS_STREAM) {
	class_stream stream;

	stream << 1 << " a " << 1.5;
	auto str = stream.str();
	cout << str << endl;
}

