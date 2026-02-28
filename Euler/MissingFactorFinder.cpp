#include "MissingFactorFinder.h"
#include "EquationSolver.h"
#include "SkipIndexIterator.h"

MissingFactorFinder::MissingFactorFinder(std::pair<Product, int>& factor, std::pair<Product, int>& unFactored)
	: factor(factor)
	, unFactored(unFactored)
{

}

bool MissingFactorFinder::operator()(const Equation& equation)
{
	const std::map<Product, int>& members = equation.GetMembers();

	if (members.size() < 3)
	{
		return false;
	}

	EquationSolver solver;
	std::vector<std::pair<Product, int>> products;

	for (std::map<Product, int>::const_iterator it = members.begin(); it != members.end(); ++it)
	{
		products.push_back(*it);
	}

	for (size_t i = 0; i < products.size(); ++i)
	{
		SkipIndexIterator<std::pair<Product, int>> it(products, i);

		factor = solver.Factor(it.Next(), it.Next());

		while (!it.IsFinished())
		{
			factor = solver.Factor(factor, it.Next());
		}

		if (factor.first.GetSize() > 0)
		{
			unFactored = products.at(i);
			return true;
		}
	}
	return false;
}