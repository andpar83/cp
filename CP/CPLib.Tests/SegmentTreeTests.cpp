#include "pch.h"
#include <algorithm>
#include <numeric>
#include <CppUnitTest.h>
#include "../CPLib/segment_tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPLibTests
{

TEST_CLASS(SegmentTreeTests)
{
public:
	TEST_METHOD(TestMinBuild)
	{
		std::vector<int> v = { 3, 2, 4, 6, 1 };
		// { 3, 2, 4, 6, 1 }
		cp::segment_tree<> st(v);
		
		Assert::AreEqual(1, st.query(0, 4));
		Assert::AreEqual(1, st.query(2, 4));
		Assert::AreEqual(2, st.query(1, 3));
		Assert::AreEqual(4, st.query(2, 3));
		Assert::AreEqual(3, st.query(0, 0));
		Assert::AreEqual(6, st.query(3, 3));
	}

	TEST_METHOD(TestMinPointAdd)
	{
		std::vector<int> v = { 3, 2, 4, 6, 1 };
		// { 3, 2, 4, 6, 1 }
		cp::segment_tree<> st(v);

		st.add(2, 2);
		// { 3, 2, 6, 6, 1 }
		Assert::AreEqual(1, st.query(2, 4));

		st.add(4, 1);
		// { 3, 2, 6, 6, 2 }
		Assert::AreEqual(2, st.query(2, 4));
		Assert::AreEqual(2, st.query(1, 3));
		Assert::AreEqual(2, st.query(0, 4));
		Assert::AreEqual(3, st.query(0, 0));
		Assert::AreEqual(3, st.query(0));
		Assert::AreEqual(6, st.query(2, 3));

		st.add(0, 5);
		// { 8, 2, 6, 6, 2 }
		Assert::AreEqual(2, st.query(0, 4));
		Assert::AreEqual(8, st.query(0, 0));
		Assert::AreEqual(8, st.query(0));

		st.add(2, 1);
		// { 8, 2, 7, 6, 2 }
		Assert::AreEqual(7, st.query(2, 2));
		Assert::AreEqual(7, st.query(2));
		Assert::AreEqual(2, st.query(0, 4));
		Assert::AreEqual(6, st.query(2, 3));
		Assert::AreEqual(2, st.query(2, 4));
	}

	TEST_METHOD(TestMinRangeAdd)
	{
		std::vector<int> v = { 3, 2, 4, 6, 1 };
		// { 3, 2, 4, 6, 1 }
		cp::segment_tree<> st(v);

		st.add(2, 4, 2);
		// { 3, 2, 6, 8, 3 }
		Assert::AreEqual(3, st.query(2, 4));
		Assert::AreEqual(6, st.query(2, 3));

		st.add(1, 2, 1);
		// { 3, 3, 7, 8, 3 }
		Assert::AreEqual(3, st.query(2, 4));
		Assert::AreEqual(3, st.query(1, 3));
		Assert::AreEqual(3, st.query(0, 4));
		Assert::AreEqual(3, st.query(1, 1));
		Assert::AreEqual(3, st.query(1));
		Assert::AreEqual(7, st.query(2, 3));

		st.add(0, 2, 5);
		// { 8, 8, 12, 8, 3 }
		Assert::AreEqual(3, st.query(0, 4));
		Assert::AreEqual(8, st.query(0, 0));
		Assert::AreEqual(8, st.query(0));
		Assert::AreEqual(8, st.query(1, 2));
		Assert::AreEqual(12, st.query(2, 2));
		Assert::AreEqual(12, st.query(2));
		Assert::AreEqual(8, st.query(1, 3));

		st.add(2, 4, 10);
		// { 8, 8, 22, 18, 13 }
		Assert::AreEqual(22, st.query(2, 2));
		Assert::AreEqual(22, st.query(2));
		Assert::AreEqual(8, st.query(0, 4));
		Assert::AreEqual(18, st.query(2, 3));
		Assert::AreEqual(13, st.query(2, 4));
		Assert::AreEqual(8, st.query(1, 2));
	}
};

}