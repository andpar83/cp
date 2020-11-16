#pragma once
#include <cassert>
#include <vector>
#include <unordered_map>
#include <limits>
#include <stdexcept>

namespace cp
{
	
/// <summary>
/// Basic Fenwick Tree (Binary Indexed Tree)(BIT) implementation.
/// It supports point update and range sum queries in O(log n) time.
/// </summary>
/// <typeparam name="T">Integer type (int or long long usually) representing elements in the tree.</typeparam>
/// <typeparam name="Container">
/// Underlying container to store data.
/// Usually it's a vector which holds entire range
/// but if elements are sparse and range is big, this approach won't work.
/// unordered_map works in this case.
/// </typeparam>
/// <remarks>
/// Another approach to handle huge sparse ranges is to re-map original elements to contiguous range
/// and use vector as underlying container. Like, if we have range [1, 10^15] but just update elements
/// in positions 10^9, 10^12 and 10^15, we could re-map them to the elements [0, 1, 2] and use vector.
/// Basically, using unordered_map does something similar internally.
/// </remarks>
/// <see cref="https://cp-algorithms.com/data_structures/fenwick.html"/>
/// <see cref="https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/"/>
/// <example>
/*

	// Creates FenwickTree with 5 elements with indexes from 0 to 4 and values 0
	// Corresponds to this array [0, 0, 0, 0, 0]
	cp::fenwick_tree<long long> ft(5);

	// Adds value 3 to the element in position 2
	// Corresponds to this array [0, 0, 3, 0, 0]
	ft.add(2, 3);
	// Adds value 1 to the element in position 4
	// Corresponds to this array [0, 0, 3, 0, 1]
	ft.add(4, 1);

	// Returns sum of the elements in positions from 2 to 4 inclusive: 3 + 0 + 1
	auto sum = ft.sum(2, 4);

	////////////////////////////////////////////////////////////////////////////////

	// Creates FenwickTree with 10^15 elements with indexes from 0 to 10^15 - 1 and values 0
	// Corresponds to this array of size 10^15 [0, 0, ..., 0, 0]
	cp::fenwick_tree<long long, std::unordered_map<unsigned long long, long long>> ft(1000'000'000'000'000ULL);

	// Adds value 3 to the element in position 10^12
	ft.add(1000'000'000'000ULL, 3);
	// Adds value 1 to the element in position 10^15 - 1
	ft.add(1000'000'000'000'000ULL - 1, 1);

	// Returns sum of the elements in positions from 10^12 + 1 to 10^15 - 1 inclusive: 1
	auto sum = ft.sum(1000'000'000'000ULL + 1, 1000'000'000'000'000ULL - 1);
*/
/// </example>
template <typename T = int, typename Container = std::vector<T>>
class fenwick_tree
{
	template <typename TraitContainer>
	struct container_trait
	{
		static const bool supported = false;
	};

	template <typename TraitContainerElement>
	struct container_trait<std::vector<TraitContainerElement>>
	{
		static const bool supported = true;
		using index_t = size_t;
		
		static void init(std::vector<TraitContainerElement>& container, unsigned long long size)
		{
			if (size >= std::numeric_limits<size_t>::max())
				throw std::out_of_range("size of vector is too big");
			container.resize(static_cast<size_t>(size), 0);
		}
	};

	template <typename TraitContainerElement1, typename TraitContainerElement2>
	struct container_trait<std::unordered_map<TraitContainerElement1, TraitContainerElement2>>
	{
		static const bool supported = true;
		using index_t = TraitContainerElement1;
		
		static void init(std::unordered_map<TraitContainerElement1, TraitContainerElement2>& container, unsigned long long size)
		{
			// Do nothing
		}
	};

	static_assert(container_trait<Container>::supported, "Container type is not supported. Only vector and unordered_map are supported");
	
public:
	/// <summary>
	/// Index type for underlying container. size_t for vector and key type for unordered_map.
	/// </summary>
	using index_t = typename container_trait<Container>::index_t;
	
	/// <summary>
	/// Creates a Fenwick Tree with n elements indexed from 0 to (n - 1) inclusive and initial value 0.
	/// </summary>
	/// <remarks>
	/// Complexity is O(n).
	/// </remarks>
	/// <param name="n">Number of elements in the tree.</param>
	fenwick_tree(index_t n) : n_(n + 1)
	{
		container_trait<Container>::init(ft_, n_);
	}

	/// <summary>
	/// Creates a Fenwick Tree with n elements equal to size of <paramref name="v"/> indexed from 0 to (n - 1) inclusive and initial values from <paramref name="v"/>.
	/// </summary>
	/// <remarks>
	/// Complexity is O(n * log n).
	/// </remarks>
	/// <typeparam name="TInit">Integer type of original elements. Could be different from the <typeparamref name="T"/> for example if T is long long and TInit is int.</typeparam>
	/// <param name="v">Vector with initial values.</param>
	template <typename TInit>
	fenwick_tree(const std::vector<TInit>& v) : n_(v.size() + 1)
	{
		container_trait<Container>::init(ft_, n_);
		for (size_t i = 0; i < v.size(); ++i)
			add(i, v[i]);
	}

	/// <summary>
	/// Adds value <paramref name="val"/> to the element in position <paramref name="pos"/>.
	/// </summary>
	/// <remarks>
	/// Complexity is O(log n).
	/// </remarks>
	/// <param name="pos">Element to update.</param>
	/// <param name="val">Value to add.</param>
	void add(index_t pos, T val)
	{
		for (++pos; pos < n_; pos += pos & (~pos + 1))
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
	T sum(index_t to_inclusive) // const // It's not const because could update map
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
	T sum(index_t from_inclusive, index_t to_inclusive) // const
	{
		assert(from_inclusive <= to_inclusive);
		return sum(to_inclusive) - (from_inclusive ? sum(from_inclusive - 1) : 0);
	}

private:
	const		index_t	n_;
	Container	ft_;
};

}