#include "Product.h"
#include <algorithm>

Product::Product() :
	powers()
{
}

void Product::SetPower(size_t unknown, unsigned int power)
{
	powers.resize(std::max(powers.size(), unknown + 1), 0);
	powers[unknown] = power;
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