#pragma once

#include <sstream>

class cstream
{

public :
	cstream() {}

	~cstream() {}

protected:
	std::stringstream m_stringstream;

public:

	cstream& operator << (int val) {
		m_stringstream << val;
		return *this;
	}

	cstream& operator << (const std::string val) {
		m_stringstream << val;
		return *this;
	}

	cstream& operator << (double val) {
		m_stringstream << val;
		return *this;
	}

	cstream& operator << (float val) {
		m_stringstream << val;
		return *this;
	}

	std::string str() {
		return m_stringstream.str();
	}

	void operator += (cstream& right) {
		m_stringstream << right.str();
	}

};

