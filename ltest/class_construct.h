#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


class class_construct {

public :
	class_construct() : num(new int(0))   { 
		std::cout << "default construct " << ++counter << std::endl;
		*num = counter;
	}

	class_construct(const class_construct& obj) : num(new int(*obj.num))  {
		std::cout << "copy construct " << ++counter << std::endl;
	}

	class_construct(class_construct &&obj) : num(obj.num)  {
		std::cout << "move construct " << ++counter << std::endl;
	}

	~class_construct() {}

	int get_num() { return *num; }
protected:
	int* num;
private:
	static int counter;
};

int class_construct::counter = 0;