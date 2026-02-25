#include "EquationSolver.h"
#include<vector>
#include<algorithm>

void EquationSolver::Add(Equation& result, const Equation& addition) const
{
	std::map<Product, int> members = addition.GetMembers();
	for (auto it = members.begin(); it != members.end(); ++it)
	{
		result.Add(it->first, it->second);
	}
}

Product MultiplyProducts(const Product &left, const Product &right)
{
	Product result;
	size_t size = std::max(left.GetSize(), right.GetSize());
	for (size_t k = 0; k < size; ++k)
	{
		result.SetPower(k, left.GetPower(k) + right.GetPower(k));
	}
	return result;
}

Equation EquationSolver::Multiply(int scalar, const Product& left, const Equation& right) const
{
	Equation result;
	const auto& rightMembers = right.GetMembers();

	for (auto rightIt = rightMembers.cbegin(); rightIt != rightMembers.cend(); ++rightIt)
	{
		Product member = MultiplyProducts(left, rightIt->first);
		result.Add(member, scalar * rightIt->second);
	}
	return result;
}

Equation EquationSolver::Multiply(const Equation& left, const Equation& right) const
{
	Equation result;

	const auto& leftMembers = left.GetMembers();

	for (auto leftIt = leftMembers.cbegin(); leftIt != leftMembers.cend(); ++leftIt)
	{
		Equation part = Multiply(leftIt->second, leftIt->first, right);
		Add(result, part);
	}

	return result;
}

Product EquationSolver::GreatestCommonDivisor(const Product& left, const Product& right) const
{
	Product result;
	size_t size = std::max(left.GetSize(), right.GetSize());
	for (size_t i = 0; i < size; ++i)
	{
		result.SetPower(std::min(left.GetPower(i), right.GetPower(i)));
	}
	return result;
}