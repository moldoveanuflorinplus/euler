#include "Equation.h"

Equation::Equation() :
	members()
{
}

void Equation::Add(const Product& key, int scalar)
{
	members[key] += scalar;
}

const std::map<Product, int> Equation::GetMembers() const
{
	return members;
}
