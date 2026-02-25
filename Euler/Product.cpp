#include "Product.h"
#include <algorithm>

Product::Product() :
	powers()
{
}

void TriageZeroes(std::vector<unsigned int> powers)
{
	size_t over = -1;
	for (size_t i = powers.size() - 1; i != over; --i)
	{
		if (powers[i] == 0)
		{
			powers.pop_back();
		}
		else
		{
			break;
		}
	}
}

void Product::SetPower(size_t unknown, unsigned int power)
{
	powers.resize(std::max(powers.size(), unknown + 1), 0);
	powers[unknown] = power;
	TriageZeroes(powers);
}

size_t Product::GetSize() const
{
	return powers.size();
}

unsigned int Product::GetPower(size_t unknown) const
{
	if (unknown < powers.size())
	{
		return powers[unknown];
	}
	return 0;
}

bool Product::operator<(const Product& other) const
{
	if (GetSize() < other.GetSize())
	{
		return true;
	}
	if (GetSize() > other.GetSize())
	{
		return false;
	}
	for (size_t i = 0; i < GetSize(); ++i)
	{
		if (GetPower(i) < other.GetPower(i))
		{
			return true;
		}
		if (GetPower(i) > other.GetPower(i))
		{
			return false;
		}
	}
	return false;
}