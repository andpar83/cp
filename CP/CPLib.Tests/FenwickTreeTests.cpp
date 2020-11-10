#include "pch.h"
#include <CppUnitTest.h>
#include "../CPLib/fenwick_tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPLibTests
{
	
TEST_CLASS(FenwickTreeTests)
{
public:
	TEST_METHOD(TestBasic)
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
};
	
}
