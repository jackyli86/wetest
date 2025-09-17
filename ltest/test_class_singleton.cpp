#include "stdafx.h"

#include "class_singleton.h"
class t_singleton : public class_singleton<t_singleton> {
public:
	std::string name;
	int age;
};

TEST(TEST_CLASS, TEST_CLASS_SINGLETON) {
	auto t = new t_singleton();

	auto& instance = t_singleton::instance();
	instance.name = "tester";
	instance.age = 10;

	cout << t_singleton::instance().name << "\t" << t_singleton::instance().age << endl;
}