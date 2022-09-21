#pragma once
#include "stdafx.h"

using namespace std;

TEST(TEST_STL, TEST_STL_LIST) {

	list<int> tlist;

	tlist.push_back(1);
	tlist.push_back(2);
	tlist.push_back(3);

	EXPECT_EQ(1, tlist.front());
	EXPECT_EQ(3, tlist.back());

	tlist.push_front(0);

	EXPECT_EQ(0, tlist.front());
	EXPECT_EQ(3, tlist.back());

	BUILDIN_PRINT(tlist);
	tlist.remove_if([](int value) { return value == 1 || value == 2; });
	BUILDIN_PRINT(tlist);

	tlist.unique();
	BUILDIN_PRINT(tlist);

	list<int> tlist2{ 4,5,6 };
	tlist.splice(tlist.end(), tlist2);
	BUILDIN_PRINT(tlist);
	BUILDIN_PRINT(tlist2);

	for (auto iter = tlist.begin();
		iter != tlist.end();
		) {
		if (*iter == 5 || *iter == 6) {
			iter = tlist.erase(iter);
		}
		else {
			++iter;
		}
	}
	BUILDIN_PRINT(tlist);
}