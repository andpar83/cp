#include "pch.h"
#include <algorithm>
#include <numeric>
#include <CppUnitTest.h>
#include "../CPLib/fenwick_tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPLibTests
{
	
TEST_CLASS(FenwickTreeTests)
{
public:
	TEST_METHOD(TestSizeInit)
	{
		cp::fenwick_tree<> ft(5);
		
		ft.add(2, 2);
		Assert::AreEqual(2, ft.sum(2, 4));

		ft.add(4, 1);
		Assert::AreEqual(3, ft.sum(2, 4));
		Assert::AreEqual(2, ft.sum(1, 3));
		Assert::AreEqual(3, ft.sum(0, 4));

		ft.add(0, 5);
		Assert::AreEqual(8, ft.sum(0, 4));
		
		ft.add(2, 1);
		// Element with index 2 should have value of 3 because add method adds and not overwrites existing value
		Assert::AreEqual(3, ft.sum(2, 2));
		Assert::AreEqual(9, ft.sum(0, 4));
	}

	TEST_METHOD(TestVectorInit)
	{
		std::vector<int> v(5);
		std::iota(std::begin(v), std::end(v), 1);
		cp::fenwick_tree<> ft(v);

		Assert::AreEqual(15, ft.sum(0, 4));

		ft.add(2, 2);
		Assert::AreEqual(14, ft.sum(2, 4));

		ft.add(4, 1);
		Assert::AreEqual(15, ft.sum(2, 4));
		Assert::AreEqual(11, ft.sum(1, 3));
		Assert::AreEqual(18, ft.sum(0, 4));

		ft.add(0, 5);
		Assert::AreEqual(23, ft.sum(0, 4));

		ft.add(2, 1);
		Assert::AreEqual(6, ft.sum(2, 2));
		Assert::AreEqual(24, ft.sum(0, 4));
	}

	TEST_METHOD(TestMapContainer)
	{
		cp::fenwick_tree<int, std::unordered_map<int, int>> ft(5);

		ft.add(2, 2);
		Assert::AreEqual(2, ft.sum(2, 4));

		ft.add(4, 1);
		Assert::AreEqual(3, ft.sum(2, 4));
		Assert::AreEqual(2, ft.sum(1, 3));
		Assert::AreEqual(3, ft.sum(0, 4));

		ft.add(0, 5);
		Assert::AreEqual(8, ft.sum(0, 4));

		ft.add(2, 1);
		// Element with index 2 should have value of 3 because add method adds and not overwrites existing value
		Assert::AreEqual(3, ft.sum(2, 2));
		Assert::AreEqual(9, ft.sum(0, 4));
	}

	TEST_METHOD(TestHugeIndexes)
	{
		const auto N12 = 1000'000'000'000ULL; // 10^12
		const auto N15 = 1000'000'000'000'000ULL; // 10^15
		
		cp::fenwick_tree<long long, std::unordered_map<unsigned long long, long long>> ft(N15);
		
		ft.add(N12 - 1, 2);
		ft.add(N12, 3);
		ft.add(N15 - 1, 1);

		Assert::AreEqual(5LL, ft.sum(0, N12));
		Assert::AreEqual(6LL, ft.sum(0, N15 - 1));
		Assert::AreEqual(1LL, ft.sum(N12 + 1, N15 - 1));
	}
};
	
}
