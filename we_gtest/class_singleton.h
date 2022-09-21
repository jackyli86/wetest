#pragma once

template <typename T>
class class_singleton {

protected:
	class_singleton() {};
	virtual ~class_singleton() {};

	class_singleton(const class_singleton&) = delete;

	class_singleton(class_singleton&&) = delete;

	void operator= (const class_singleton&) = delete;

public:

	static T& instance() {
		static T instance;
		return instance;
	}
};