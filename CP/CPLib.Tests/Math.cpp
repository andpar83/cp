#include "pch.h"
#include <algorithm>
#include <numeric>
#include <CppUnitTest.h>
#include "../CPLib/math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPLibTests
{

TEST_CLASS(MathTests)
{
public:
	TEST_METHOD(ModPow)
	{
		Assert::AreEqual(32, cp::mod_pow(2, 5, 1000'000'007));
	}

	TEST_METHOD(ModInverse)
	{
		Assert::AreEqual(3, cp::mod_inverse(2, 5));
		Assert::AreEqual(4, cp::mod_inverse(4, 5));
	}
};

}
