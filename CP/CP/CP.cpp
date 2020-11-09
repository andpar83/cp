#include <iostream>
#include "../CPLib/BIT_PURQ.h"

int main()
{
	BIT_PURQ<> bit(10);
	bit.add(5, 4);
	std::cout << bit.sum(2, 6) << std::endl;
}