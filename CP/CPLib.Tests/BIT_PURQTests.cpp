#include "pch.h"
#include <CppUnitTest.h>
#include "../CPLib/BIT_PURQ.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPLibTests
{
	TEST_CLASS(BIT_PURQTests)
	{
	public:
		TEST_METHOD(TestBasic)
		{
			BIT_PURQ<> bit(5);
			
			bit.add(2, 2);
			Assert::AreEqual(2, bit.sum(2, 4));

			bit.add(4, 1);
			Assert::AreEqual(3, bit.sum(2, 4));
			Assert::AreEqual(2, bit.sum(1, 3));
		}
	};
}
