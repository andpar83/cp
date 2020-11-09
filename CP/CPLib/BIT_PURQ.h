#pragma once
#include <vector>

template <typename T = int>
class BIT_PURQ
{
public:
	BIT_PURQ(size_t n) : v_(n + 1, 0)
	{
	}

	void add(size_t pos, T val)
	{
		for (++pos; pos < v_.size(); pos += pos & (~pos + 1))
			v_[pos] += val;
	}

	T sum(size_t to) const
	{
		T res = 0;
		for (++to; to > 0; to -= to & (~to + 1))
			res += v_[to];
		return res;
	}

	T sum(size_t from, size_t to) const
	{
		// TODO from could be 0
		return sum(to) - sum(from - 1);
	}

private:
	std::vector<T> v_;
};

