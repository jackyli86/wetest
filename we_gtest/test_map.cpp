#pragma once
#include <gtest/gtest.h>

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <unordered_map>

using namespace std;

TEST(TEST_STL, TEST_STL_MAP) {
	map<int, int> tmap;
	tmap.insert({ 1,1 });
	tmap.insert({ 1,2 });
	tmap.insert({ 2,2 });

	BUILDIN_PRINT(tmap);

	tmap.insert({ {3,3},{4,4},{5,5} });
	BUILDIN_PRINT(tmap);

	cout << "tmap[1] = " << tmap[1] << endl;
	cout << "tmap.at(1) = " << tmap.at(1) << endl;
	cout << "tmap.size = " << tmap.size() << endl;
	cout << "tmap.max = " << tmap.max_size() << endl;

	auto iter = tmap.end();
	iter = tmap.find(10);
	cout << "tmap.find(10) = " << (iter == tmap.end() ? "false" : "true") << endl;
	iter = tmap.find(1);
	cout << "tmap.find(1) = " << (iter == tmap.end() ? "false" : "true") << endl;

	tmap.emplace(6, 6);
	BUILDIN_PRINT(tmap);

	for (iter = tmap.begin();
		iter != tmap.end();
		) {
		if (iter->second == 5 || iter->second == 6) {
			iter = tmap.erase(iter);
		}
		else {
			++iter;
		}
	}
	BUILDIN_PRINT(tmap);

}