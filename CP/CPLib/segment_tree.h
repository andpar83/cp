#pragma once
#include <vector>
#include <optional>
#include <limits>

namespace cp
{

template <typename T = int>
class segment_tree
{
public:
	segment_tree(std::vector<T> v)
	{
		sz_ = 1;
		while (sz_ < v.size())
			sz_ *= 2;
		v.resize(sz_ + 1, std::numeric_limits<T>::max()); // TODO neutral element
		tree_.resize(2 * sz_ + 1, 0);
		add_.resize(2 * sz_ + 1, std::nullopt);
		build(v, 1, 0, sz_ - 1);
	}

	T query(size_t vec_left, size_t vec_right)
	{
		return query_impl(1, 0, sz_ - 1, vec_left, vec_right);
	}

	T query(size_t vec_pos)
	{
		return query_impl(1, 0, sz_ - 1, vec_pos, vec_pos);
	}

	void add(size_t vec_left, size_t vec_right, T val)
	{
		add_impl(1, 0, sz_ - 1, vec_left, vec_right, val);
	}

	void add(size_t vec_pos, T val)
	{
		add_impl(1, 0, sz_ - 1, vec_pos, vec_pos, val);
	}

private:
	void build(const std::vector<T>& v, size_t tree_pos, size_t tree_left, size_t tree_right)
	{
		if (tree_left == tree_right)
		{
			tree_[tree_pos] = v[tree_left];
		}
		else
		{
			auto m = tree_left + (tree_right - tree_left) / 2;
			build(v, 2 * tree_pos, tree_left, m);
			build(v, 2 * tree_pos + 1, m + 1, tree_right);
			tree_[tree_pos] = std::min(tree_[2 * tree_pos], tree_[2 * tree_pos + 1]); // TODO op
		}
	}

	void propagate(size_t tree_pos, size_t tree_left, size_t tree_right)
	{
		if (!add_[tree_pos].has_value())
			return;

		auto val = *add_[tree_pos];
		tree_[tree_pos] += val;

		if (tree_left != tree_right)
		{
			add_[2 * tree_pos] = val;
			add_[2 * tree_pos + 1] = val;
		}

		add_[tree_pos].reset();
	}

	T query_impl(size_t tree_pos, size_t tree_left, size_t tree_right, size_t vec_left, size_t vec_right)
	{
		if (vec_left > tree_right || vec_right < tree_left)
			return std::numeric_limits<T>::max(); // TODO neutral elem

		propagate(tree_pos, tree_left, tree_right);
		if (vec_left <= tree_left && tree_right <= vec_right)
			return tree_[tree_pos];
		auto m = tree_left + (tree_right - tree_left) / 2;
		auto left = query_impl(2 * tree_pos, tree_left, m, vec_left, vec_right);
		auto right = query_impl(2 * tree_pos + 1, m + 1, tree_right, vec_left, vec_right);
		return std::min(left, right); // TODO op
	}

	void add_impl(size_t tree_pos, size_t tree_left, size_t tree_right, size_t vec_left, size_t vec_right, T val)
	{
		if (vec_left > tree_right || vec_right < tree_left)
			return;

		propagate(tree_pos, tree_left, tree_right);
		if (vec_left <= tree_left && tree_right <= vec_right)
		{
			add_[tree_pos] = val;
		}
		else
		{
			auto m = tree_left + (tree_right - tree_left) / 2;
			add_impl(2 * tree_pos, tree_left, m, vec_left, vec_right, val);
			add_impl(2 * tree_pos + 1, m + 1, tree_right, vec_left, vec_right, val);
			tree_[tree_pos] = std::min(tree_[2 * tree_pos] + add_[2 * tree_pos].value_or(0), tree_[2 * tree_pos + 1] + add_[2 * tree_pos + 1].value_or(0)); // TODO op
		}
	}

private:
	size_t sz_ = 0;
	std::vector<T> tree_;
	std::vector<std::optional<T>> add_;
};

}

