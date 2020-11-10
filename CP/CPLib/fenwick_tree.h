#pragma once
#include <cassert>
#include <vector>

namespace cp
{
	
/// <summary>
/// Basic Fenwick Tree (Binary Indexed Tree)(BIT) implementation.
/// It supports point update and range sum queries in O(log n) time.
/// </summary>
/// <typeparam name="T">Integer type (int or long long usually) representing elements in the tree.</typeparam>
/// <see cref="https://cp-algorithms.com/data_structures/fenwick.html"/>
/// <see cref="https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/"/>
/// <example>
/*

	// Creates FenwickTree with 5 elements with indexes from 0 to 4 and values 0
	// Corresponds to this array [0, 0, 0, 0, 0]
	cp::fenwick_tree<long long> ft(5);

	// Adds value 3 to the element in position 0
	// Corresponds to this array [0, 0, 3, 0, 0]
	ft.add(2, 3);
	// Adds value 3 to the element in position 0
	// Corresponds to this array [0, 0, 3, 0, 1]
	ft.add(4, 1);

	// Returns sum of the elements in positions from 2 to 4 inclusive: 3 + 0 + 1
	auto sum = ft.sum(2, 4);

*/
/// </example>
template <typename T = int>
class fenwick_tree
{
public:
	/// <summary>
	/// Creates a Fenwick Tree with n elements indexed from 0 to (n - 1) inclusive and initial value 0.
	/// </summary>
	/// <param name="n">Number of elements in the tree.</param>
	fenwick_tree(size_t n) : ft_(n + 1, 0)
	{
	}

	/// <summary>
	/// Adds value <paramref name="val"/> to the element in position <paramref name="pos"/>.
	/// </summary>
	/// <remarks>
	/// Complexity is O(log n).
	/// </remarks>
	/// <param name="pos">Element to update.</param>
	/// <param name="val">Value to add.</param>
	void add(size_t pos, T val)
	{
		for (++pos; pos < ft_.size(); pos += pos & (~pos + 1))
			ft_[pos] += val;
	}

	/// <summary>
	/// Returns sum of the elements from 0 to <paramref name="to_inclusive"/> inclusive.
	/// </summary>
	/// <remarks>
	/// Complexity is O(log n).
	/// </remarks>
	/// <param name="to_inclusive">
	/// Right bound of the interval to sum. Could be from 0 to n - 1 (inclusive).
	/// Left bound is 0.
	/// </param>
	/// <returns>Sum of the elements from 0 to <paramref name="to_inclusive"/> inclusive.</returns>
	T sum(size_t to_inclusive) const
	{
		T res = 0;
		for (auto i = to_inclusive + 1; i > 0; i -= i & (~i + 1))
			res += ft_[i];
		return res;
	}

	/// <summary>
	/// Returns sum of the elements from <paramref name="from_invlusive"/> to <paramref name="to_inclusive"/> inclusive.
	/// </summary>
	/// <remarks>
	/// Complexity is O(log n).
	/// </remarks>
	/// <param name="from_inclusive">Left bound of the interval to sum. Could be from 0 to n - 1 (inclusive).</param>
	/// <param name="to_inclusive">
	/// Right bound of the interval to sum. Could be from 0 to n - 1 (inclusive).
	/// Should be greater or equal to <paramref name="from_inclusive"/>.
	/// </param>
	/// <returns>Sum of the elements from <paramref name="from_invlusive"/> to <paramref name="to_inclusive"/> inclusive.</returns>
	T sum(size_t from_inclusive, size_t to_inclusive) const
	{
		assert(from_inclusive <= to_inclusive);
		return sum(to_inclusive) - (from_inclusive ? sum(from_inclusive - 1) : 0);
	}

private:
	std::vector<T> ft_;
};

}