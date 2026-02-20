#include "Solver.h"
#include<vector>
#include<algorithm>

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

Equation Solver::Multiply(const Equation& left, const Equation& right) const
{
	Equation result;

	const auto& leftMembers = left.GetMembers();
	const auto& rightMembers = right.GetMembers();

	for (auto leftIt = leftMembers.cbegin(); leftIt != leftMembers.cend(); ++leftIt)
	{
		for (auto rightIt = rightMembers.cbegin(); rightIt != rightMembers.cend(); ++rightIt)
		{
			Product member = MultiplyProducts(leftIt->first, rightIt->first);
			result.Add(member, leftIt->second * rightIt->second);
		}
	}

	return result;
}
