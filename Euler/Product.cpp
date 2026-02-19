#include "Product.h"
#include <algorithm>

Product::Product() :
	scalar(1),
	powers()
{
}

Product::Product(int scalar) :
	scalar(scalar),
	powers()
{
}

void Product::SetScalar(int scalar)
{
	this->scalar = scalar;
}

void Product::SetPower(size_t unknown, unsigned int power)
{
	powers.resize(std::max(powers.size(), unknown + 1), 0);
	powers[unknown] = power;
}

int Product::GetScalar() const
{
	return scalar;
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