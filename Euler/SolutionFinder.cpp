#include "SolutionFinder.h"
#include "EquationSolver.h"

SolutionFinder::SolutionFinder(Equation& found, size_t& unknown, int& scalar)
	: found(found)
	, unknown(unknown)
	, scalar(scalar)
{

}

bool HasSingleUnknown(const Product& product, size_t& unknown)
{
	bool found = false;
	size_t i = 0;
	for (; i < product.GetSize(); ++i)
	{
		if (product.GetPower(i) > 1)
		{
			return false;
		}
		if (product.GetPower(i) == 1)
		{
			unknown = i;
			found = true;
		}
	}
	for (; i < product.GetSize(); ++i)
	{
		if (product.GetPower(i) > 0)
		{
			return false;
		}
	}
	return found;
}

bool HasPositiveScalar(const std::pair<Product, int>& product)
{
	return product.second > 0;
}

bool CheckPositveForSolution(const Equation& equation, size_t& unknown)
{
	const std::map<Product, int>& members = equation.GetMembers();
	std::map<Product, int>::const_iterator positiveIt = std::find_if(members.begin(), members.end(), HasPositiveScalar);

	if (positiveIt == members.end())
	{
		return false;
	}

	if (positiveIt->second > 1)
	{
		return false;
	}

	Product found = positiveIt->first;

	++positiveIt;
	positiveIt = std::find_if(positiveIt, members.end(), HasPositiveScalar);

	if (positiveIt != members.end())
	{
		return false;
	}

	return HasSingleUnknown(found, unknown);
}

bool SolutionFinder::operator()(const Equation& equation)
{
	EquationSolver solver;
	if (CheckPositveForSolution(equation, unknown))
	{
		scalar = 1;
		found = equation;
		return true;
	}
	Equation flip = solver.Multiply(-1, equation);
	if (CheckPositveForSolution(flip, unknown))
	{
		scalar = -1;
		found = equation;
		return true;
	}
	return false;
}
