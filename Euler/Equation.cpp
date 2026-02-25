#include "Equation.h"

Equation::Equation() :
	members()
{
}

void Equation::Add(const Product& key, int scalar)
{
	members[key] += scalar;
	if (members[key] == 0)
	{
		members.erase(key);
	}
}

const std::map<Product, int> Equation::GetMembers() const
{
	return members;
}

Equation Equation::One()
{
	Equation result;
	Product product;

	result.Add(product, 1);

	return result;
}