#include <iostream>
#include "../CPLib/fenwick_tree.h"

int main()
{
	cp::fenwick_tree<long long, std::unordered_map<unsigned long long, long long>> ft(1000'000'000'000'000ULL);

	ft.add(1000'000'000'000ULL - 1, 2);
	ft.add(1000'000'000'000ULL, 3);
	ft.add(1000'000'000'000'000ULL - 1, 1);

	std::cout << ft.sum(0, 1000'000'000'000ULL) << std::endl;
	std::cout << ft.sum(0, 1000'000'000'000'000ULL - 1) << std::endl;
	std::cout << ft.sum(1000'000'000'000ULL + 1, 1000'000'000'000'000ULL - 1) << std::endl;
}