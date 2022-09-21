#pragma once

#include <sstream>

class class_stream
{

public :
	class_stream() {}

	~class_stream() {}

protected:
	std::stringstream m_stringstream;

public:

	class_stream& operator << (int val) {
		m_stringstream << val;
		return *this;
	}

	class_stream& operator << (const std::string val) {
		m_stringstream << val;
		return *this;
	}

	class_stream& operator << (double val) {
		m_stringstream << val;
		return *this;
	}

	class_stream& operator << (float val) {
		m_stringstream << val;
		return *this;
	}

	std::string str() {
		return m_stringstream.str();
	}

	void operator += (class_stream& right) {
		m_stringstream << right.str();
	}

};

