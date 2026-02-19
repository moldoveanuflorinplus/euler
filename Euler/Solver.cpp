#include "Solver.h"
#include<vector>
#include<algorithm>

void MultiplyProducts(const Product &left, const Product &right, Product& result)
{
	result.SetScalar(left.GetScalar() * right.GetScalar());
	size_t unknownSize = std::max(left.GetSize(), right.GetSize());
	for (size_t k = 0; k < unknownSize; ++k)
	{
		result.SetPower(k, left.GetPower(k) + right.GetPower(k));
	}
}

Equation Solver::Multiply(const Equation& left, const Equation& right) const
{
	Equation result(left.GetSize() * right.GetSize());

	for (size_t i = 0; i < left.GetSize(); ++i)
	{
		const Product& leftMember = left.GetMember(i);
		for (size_t j = 0; j < right.GetSize(); ++j)
		{
			const Product& rightMember = right.GetMember(j);
			Product& productResult = result.GetMember(i * right.GetSize() + j);

			MultiplyProducts(leftMember, rightMember, productResult);
		}
	}

	return result;
}
