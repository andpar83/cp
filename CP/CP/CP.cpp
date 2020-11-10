#include <iostream>
#include "../CPLib/fenwick_tree.h"

int main()
{
	cp::fenwick_tree<> bit(10);
	bit.add(5, 4);
	std::cout << bit.sum(2, 6) << std::endl;
}