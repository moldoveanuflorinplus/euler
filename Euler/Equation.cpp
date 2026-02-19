#include "Equation.h"

Equation::Equation() :
	members()
{
}

Equation::Equation(size_t amount) :
	members(amount, Product())
{
}


void Equation::Add(const Product& member)
{
	members.push_back(member);
}

size_t Equation::GetSize() const
{
	return members.size();
}

Product& Equation::GetMember(size_t index)
{
	return members.at(index);
}

const Product& Equation::GetMember(size_t index) const
{
	return members.at(index);
}
