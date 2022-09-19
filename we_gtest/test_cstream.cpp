#pragma once
#include <gtest/gtest.h>


#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "cstream.h"

TEST(TEST_CSTREAM, TEST_CSTREAM) {
	cstream stream, stream2;

	stream << 1 << " a " << 1.5;
	stream2 << "stream2" << 1 << 2.6;

	//stream + stream2;
}

