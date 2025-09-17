#pragma once

#include <sstream>
#include <utility>

// map unordered_map
template <typename A, typename B>
std::stringstream print_elem(const std::pair<A,B>& elem) {
	std::stringstream stream;
	stream << "(" << elem.first << "," << elem.second << ")";
	return stream;
}

// list vector set
template <typename A>
std::stringstream print_elem(const A& elem) {
	std::stringstream stream;
	stream << elem;
	return stream;
}

template <typename C>
std::stringstream buildin_print_elem(const C& c) {
	std::stringstream stream;
	stream << "{";
	for (const auto& elem : c) {
		stream << print_elem(elem).str() << ", ";
	}
	stream << "}";

	return stream;
}


#define BUILDIN_PRINT(container) \
	do {\
		std::cout << "line:"<< __LINE__ << "\t"<< #container << "\t" << container.size() << "\t" << buildin_print_elem(container).str() << std::endl; \
	} while (0);
