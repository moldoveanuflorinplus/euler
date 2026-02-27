#include <numeric>
#include <set>
#include "EquationAnalizer.h"
#include "EquationSolver.h"
#include "PowerIterator.h"
#include "Replacer.h"
#include "SkipIndexIterator.h"
#include "SystemSimplifier.h"

System Replace(const System& system, const size_t unknown, const Equation& solution)
{
	System result;

	std::vector<Equation> equalities = system.GetEqualities();
	for (std::vector<Equation>::const_iterator it = equalities.begin(); it != equalities.end(); ++it)
	{
		Replacer replacer;
		result.AddEquality(replacer.Replace(*it, unknown, solution));
	}

	std::vector<Equation> solutions = system.GetSolutions();
	for (std::vector<Equation>::const_iterator it = solutions.begin(); it != solutions.end(); ++it)
	{
		Replacer replacer;
		result.AddSolution(replacer.Replace(*it, unknown, solution));
	}

	return result;
}

bool GetProductWithMissingFactor(const Equation& equation, std::pair<Product, int>& factor, std::pair<Product, int>& unFactored)
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

bool GetFirstProductWithMissingFactor(const System& system, std::pair<Product, int>& factor, std::pair<Product, int>& unFactored)
{
	const std::vector<Equation>& equalities = system.GetEqualities();

	for (std::vector<Equation>::const_iterator it = equalities.begin(); it != equalities.end(); ++it)
	{
		if (GetProductWithMissingFactor(*it, factor, unFactored))
		{
			return true;
		}
	}
	return false;
}

void AddNewEquations(System& system)
{
	std::pair<Product, int> factor;
	std::pair<Product, int> unFactored;

	if (GetFirstProductWithMissingFactor(system, factor, unFactored))
	{
		EquationAnalizer analizer;
		Equation newEquality;
			
		newEquality.Add(unFactored.first, std::abs(unFactored.second));
		factor.first.SetPower(analizer.GetNextUnknown(system), 1);
		newEquality.Add(factor.first, -factor.second);

		system.AddEquality(newEquality);
	}
}

int Sign(int nonZeroScalar)
{
	return nonZeroScalar > 0 ? 1 : -1;
}

bool GetPair(const Equation& equation, std::pair<Product, int>& left, std::pair<Product, int>& right)
{
	const std::map<Product, int>& members = equation.GetMembers();
	if (members.size() != 2)
	{
		return false;
	}

	std::map<Product, int>::const_iterator it = members.begin();
	left = *it;
	++it;
	right = *it;

	return true;
}

bool IsPairWithDifferentSigns(const Equation& equation, std::pair<Product, int>& left, std::pair<Product, int>& right)
{
	if (GetPair(equation, left, right))
	{
		return Sign(left.second) != Sign(right.second);
	}
	return false;
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

bool HasNegativeScalar(const std::pair<Product, int>& product)
{
	return product.second < 0;
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

bool IsSolution(const Equation& equation, size_t& unknown, int& scalar)
{
	EquationSolver solver;
	if (CheckPositveForSolution(equation, unknown))
	{
		scalar = 1;
		return true;
	}
	Equation flip = solver.Multiply(-1, equation);
	if (CheckPositveForSolution(flip, unknown))
	{
		scalar = -1;
		return true;
	}
	return false;
}

Equation ConvertToSolution(const Equation& equation, const size_t unknown, const int scalar)
{
	Product remove;
	remove.SetPower(unknown, 1);

	Equation result = equation;
	result.Add(remove, -scalar);

	return result;
}

std::map<size_t, Equation> FindNewSolutions(const System& system)
{
	const std::vector<Equation>& equalities = system.GetEqualities();
	for (std::vector<Equation>::const_iterator it = equalities.begin(); it != equalities.end(); ++it)
	{
		size_t unknown;
		int scalar;
	
		if (IsSolution(*it, unknown, scalar))
		{
			std::map<size_t, Equation> result;
			Equation solution = ConvertToSolution(*it, unknown, scalar);
			result.insert({unknown, solution});

			return result;
		}
	}
	return std::map<size_t, Equation>();
}

std::pair<Product, int> GetCommonFactor(const Equation& equation)
{
	EquationSolver solver;
	const std::map<Product, int>& products = equation.GetMembers();

	std::map<Product, int>::const_iterator it = products.begin();
	std::pair<Product, int> result = *it;

	for (++it; it != products.end(); ++it)
	{
		result = solver.Factor(result, *it);
	}
	return result;
}

Equation RemoveCommonFactors(const Equation& equation)
{
	EquationSolver solver;
	std::pair<Product, int> factor = GetCommonFactor(equation);
	Equation result = solver.Divide(equation, factor);

	return result;
}

System RemoveCommonFactors(const System& system)
{
	System result;

	const std::vector<Equation>& equalities = system.GetEqualities();
	for (std::vector<Equation>::const_iterator it = equalities.begin(); it != equalities.end(); ++it)
	{
		result.AddEquality(RemoveCommonFactors(*it));
	}

	const std::vector<Equation>& solutions = system.GetSolutions();
	for (std::vector<Equation>::const_iterator it = solutions.begin(); it != solutions.end(); ++it)
	{
		result.AddSolution(*it);
	}
	return result;
}

Product RemoveUnknowns(const Product& product, std::pair<size_t, size_t> interval)
{
	Product result;

	size_t intervalSize = interval.second - interval.first + 1;

	for (size_t i = 0; i < interval.first; ++i)
	{
		result.SetPower(i, product.GetPower(i));
	}

	for (size_t i = interval.second + 1; i < product.GetSize(); ++i)
	{
		result.SetPower(i - intervalSize, product.GetPower(i));
	}

	return result;
}

Equation RemoveUnknowns(const Equation& equation, std::pair<size_t, size_t> interval)
{
	Equation result;

	const std::map<Product, int>& members = equation.GetMembers();
	for (std::map<Product, int>::const_iterator it = members.begin(); it != members.end(); ++it)
	{
		result.Add(RemoveUnknowns(it->first, interval), it->second);
	}

	return result;
}

System RemoveUnknowns(const System& system, std::pair<size_t, size_t> interval)
{
	System result;

	const std::vector<Equation>& equalities = system.GetEqualities();
	for (std::vector<Equation>::const_iterator it = equalities.begin(); it != equalities.end(); ++it)
	{
		result.AddEquality(RemoveUnknowns(*it, interval));
	}

	const std::vector<Equation>& solutions = system.GetSolutions();
	for (std::vector<Equation>::const_iterator it = solutions.begin(); it != solutions.end(); ++it)
	{
		result.AddSolution(RemoveUnknowns(*it, interval));
	}

	return result;
}

void CollectUnknowns(const Product& product, std::set<size_t>& unknowns)
{
	for (size_t i = 0; i < product.GetSize(); ++i)
	{
		if (product.GetPower(i) > 0)
		{
			unknowns.insert(i);
		}
	}
}

void CollectUnknowns(const Equation& equation, std::set<size_t>& unknowns)
{
	const std::map<Product, int>& members = equation.GetMembers();
	for (std::map<Product, int>::const_iterator it = members.begin(); it != members.end(); ++it)
	{
		CollectUnknowns(it->first, unknowns);
	}
}

void CollectUnknowns(const System& system, std::set<size_t>& unknowns)
{
	const std::vector<Equation>& equalities = system.GetEqualities();
	for (std::vector<Equation>::const_iterator it = equalities.begin(); it != equalities.end(); ++it)
	{
		CollectUnknowns(*it, unknowns);
	}

	for (size_t i = 0; i < system.GetSolutions().size(); ++i)
	{
		unknowns.insert(i);
	}

	const std::vector<Equation>& solutions = system.GetSolutions();
	for (std::vector<Equation>::const_iterator it = solutions.begin(); it != solutions.end(); ++it)
	{
		CollectUnknowns(*it, unknowns);
	}
}

std::vector<std::pair<size_t, size_t>> ToInteravals(const std::set<size_t>& unknowns)
{
	std::vector<std::pair<size_t, size_t>> intervals;

	if (unknowns.size() == 0)
	{
		return intervals;
	}

	std::set<size_t>::const_iterator it = unknowns.begin();
	size_t start = *it;
	size_t current = start;

	for (++it; it != unknowns.end(); ++it)
	{
		if (current + 1 == *it)
		{
			++current;
		}
		else
		{
			intervals.push_back({ start, current });
			start = *it;
			current = start;
		}
	}
	intervals.push_back({ start, current });
	return intervals;
}

std::set<size_t> GetUnusedUnknowns(const std::set<size_t>& unknowns)
{
	std::set<size_t> unused;
	for (size_t i = 0; i < *unknowns.rbegin(); ++i)
	{
		if (unknowns.find(i) == unknowns.end())
		{
			unused.insert(i);
		}
	}
	return unused;
}

System RemoveUnusedUnknowns(const System& system)
{
	System result = system;

	std::set<size_t> usedUnknowns;
	CollectUnknowns(system, usedUnknowns);
	std::set<size_t> unusedUnknowns = GetUnusedUnknowns(usedUnknowns);

	const std::vector<std::pair<size_t, size_t>> intervals = ToInteravals(unusedUnknowns);

	for (std::vector<std::pair<size_t, size_t>>::const_reverse_iterator it = intervals.rbegin(); it != intervals.rend(); ++it)
	{
		result = RemoveUnknowns(result, *it);
	}

	return result;
}

System SystemSimplifier::Simplify(const System& system, const std::map<size_t, Equation>& solutions) const
{
	System result = system;

	std::map<size_t, Equation> nextSolutions = solutions;

	while(nextSolutions.size() > 0)
	{
		for (std::map<size_t, Equation>::const_iterator it = nextSolutions.begin(); it != nextSolutions.end(); ++it)
		{
			result = Replace(result, it->first, it->second);
		}
		result = RemoveCommonFactors(result);
		result = RemoveUnusedUnknowns(result);

		nextSolutions = FindNewSolutions(result);
	}
	AddNewEquations(result);

	return result;
}