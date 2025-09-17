#include "stdafx.h"

TEST(TEST_STL, TEST_STL_VECTOR) {

	vector<int> v1{1,2,3,4,5}, v2;
	EXPECT_EQ(5, v1.size());
	EXPECT_EQ(1, v1.front());
	EXPECT_EQ(5, v1.back());


	v1.push_back(6);
	EXPECT_EQ(6, v1.back());


	v1.insert(v1.end(), 7);
	EXPECT_EQ(7, v1.back());

	v1.insert(v1.end(), { 8,9,10 });
	EXPECT_EQ(10, v1.back());


	v1.pop_back();
	EXPECT_EQ(9, v1.back());


	EXPECT_EQ(v1.at(0), v1[0]);
	EXPECT_EQ(v1.at(0), v1.front());

	v1.assign({31,32,33,34,35,36,37,38,39 });
	EXPECT_EQ(9, v1.size());
	EXPECT_EQ(31, v1.front());
	EXPECT_EQ(39, v1.back());

	v1.emplace(v1.end(),39);
	EXPECT_EQ(10, v1.size());
	EXPECT_EQ(39, v1.back());

	v1.emplace_back(40);
	EXPECT_EQ(11, v1.size());
	EXPECT_EQ(40, v1.back());

	v2.assign({ 51,52 });
	v1.swap(v2);
	EXPECT_EQ(2, v1.size());
	EXPECT_EQ(11, v2.size());
	BUILDIN_PRINT(v1);
	BUILDIN_PRINT(v2);


	v2.resize(12);
	EXPECT_EQ(12, v2.size());
	EXPECT_EQ(0, v2.back());


	v2.resize(10);
	EXPECT_EQ(10, v2.size());
	EXPECT_EQ(39, v2.back());

	v2.shrink_to_fit();
	EXPECT_EQ(v2.capacity(), v2.size());
	v2.reserve(100);
	EXPECT_EQ(100, v2.capacity());

	for (auto iter = v2.begin();
		iter != v2.end();
		) {
		if (*iter == 31 || *iter == 32) {
			iter = v2.erase(iter);
		}
		else {
			++iter;
		}

	}
}



