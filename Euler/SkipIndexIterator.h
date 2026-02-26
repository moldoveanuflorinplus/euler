#pragma once
#include <vector>

template<class T>
class SkipIndexIterator
{
private:
	const std::vector<T>& base;
	size_t skip;
	size_t index;
	size_t end;

public:
	SkipIndexIterator(const std::vector<T>& base, size_t skip)
		: base(base)
		, skip(skip)
		, index(skip == 0 ? 1 : 0)
		, end(base.size() - (base.size() == skip ? 2 : 1))
	{
	}

	const T& Next()
	{
		const T& current = base.at(index);
		++index;
		if (index == skip)
		{
			++index;
		}
		return current;
	}

	bool IsFinished() const
	{
		return index > end;
	}
};

