#pragma once

#include <iostream>


#define BUILDIN_PRINT(container) \
	do {\
		std::stringstream stream; \
		stream << "{"; \
		for(auto value : container) {\
			stream << value << ","; \
		} \
		stream << "}"; \
		std::cout << "line:"<< __LINE__ << "\t"<< #container << "\t" << container.size() << "\t" << stream.str() << std::endl; \
	} while (false);