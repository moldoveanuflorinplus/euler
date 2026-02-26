#include "PowerIterator.h"

PowerIterator::PowerIterator(const std::vector<size_t>& max)
	: max(max)
	, index(max.size(), 0)
{
}

bool PowerIterator::Next()
{
	for (size_t i = 0; i < max.size(); ++i)
	{
		++index[i];
		if (index[i] > max[i])
		{
			index[i] = 0;
			continue;
		}
		return true;
	}
	return false;
}

const std::vector<size_t>& PowerIterator::GetIndex() const
{
	return index;
}
