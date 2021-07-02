#pragma once
#include <cassert>

namespace cp
{

// (a ^ b) % mod.
// Not sure if it's ok but https://cses.fi/problemset/task/1095 thinks that 0 ^ 0 == 1.
template <typename T>
T mod_pow(T a, T b, T mod)
{
	assert(b >= 0);

	T result = 1;
	a = a % mod;
	for (; b; b >>= 1, a = (a * a) % mod)
	{
		if (b & 1)
			result = (result * a) % mod;
	}

	return result;
}

// Multiplicative modulo inverse.
// a * mod_inverse(a, mod) % mod == 1.
// mod should be prime.
// By Little Fermat Theorem: a ^ (mod - 1) % mod == 1  ==> a ^ (mod - 2) % mod == a ^ (-1) % mod.
template <typename T>
T mod_inverse(T a, T mod)
{
	return mod_pow(a, mod - 2, mod);
}

}