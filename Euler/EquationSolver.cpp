#include "EquationSolver.h"
#include<algorithm>
#include<numeric>
#include<vector>

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

Equation EquationSolver::Multiply(int scalar, const Equation& right) const
{
	Equation result;
	const auto& rightMembers = right.GetMembers();

	for (auto rightIt = rightMembers.cbegin(); rightIt != rightMembers.cend(); ++rightIt)
	{
		result.Add(rightIt->first, scalar * rightIt->second);
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

std::pair<Product, int> EquationSolver::Factor(const std::pair<Product, int>& left, const std::pair<Product, int>& right) const
{
	return std::pair<Product, int>(Factor(left.first, right.first), std::gcd(left.second, right.second));
}

Product EquationSolver::Factor(const Product& left, const Product& right) const
{
	Product result;
	size_t size = std::max(left.GetSize(), right.GetSize());
	for (size_t i = 0; i < size; ++i)
	{
		result.SetPower(i, std::min(left.GetPower(i), right.GetPower(i)));
	}
	return result;
}

Equation EquationSolver::Divide(const Equation& divident, const std::pair<Product, int>& divisor) const
{
	Equation result;
	const std::map<Product, int>& products = divident.GetMembers();
	for (std::map<Product, int>::const_iterator it = products.begin(); it != products.end(); ++it)
	{
		std::pair<Product, int> product = Divide(*it, divisor);
		result.Add(product.first, product.second);
	}

	return result;
}

std::pair<Product, int> EquationSolver::Divide(const std::pair<Product, int>& divident, const std::pair<Product, int>& divisor) const
{
	std::pair<Product, int> result = divident;

	for (size_t i = 0; i < result.first.GetSize(); ++i)
	{
		result.first.SetPower(i, result.first.GetPower(i) - divisor.first.GetPower(i));
	}
	result.second /= divisor.second;
	return result;
}