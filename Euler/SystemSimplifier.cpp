#include <algorithm>
#include <numeric>
#include <set>

#include "EquationAnalizer.h"
#include "EquationSolver.h"
#include "MissingFactorFinder.h"
#include "PowerIterator.h"
#include "Replacer.h"
#include "SolutionFinder.h"
#include "SystemSimplifier.h"

System Replace(const System& system, const size_t unknown, const Equation& solution)
{
	System result;
	Replacer replacer;

	std::vector<Equation> equalities = system.GetEqualities();
	for (std::vector<Equation>::const_iterator it = equalities.begin(); it != equalities.end(); ++it)
	{
		result.AddEquality(replacer.Replace(*it, unknown, solution));
	}

	std::vector<Equation> solutions = system.GetSolutions();
	for (std::vector<Equation>::const_iterator it = solutions.begin(); it != solutions.end(); ++it)
	{
		result.AddSolution(replacer.Replace(*it, unknown, solution));
	}

	return result;
}

void AddNewEquations(System& system)
{
	std::pair<Product, int> factor;
	std::pair<Product, int> unFactored;

	MissingFactorFinder finder(factor, unFactored);

	const std::vector<Equation>& equalities = system.GetEqualities();
	if (std::any_of(equalities.begin(), equalities.end(), finder))
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
	return GetPair(equation, left, right) && Sign(left.second) != Sign(right.second);
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

	Equation equation;
	size_t unknown;
	int scalar;

	SolutionFinder finder(equation, unknown, scalar);

	if (std::any_of(equalities.begin(), equalities.end(), finder))
	{
		Equation solution = ConvertToSolution(equation, unknown, scalar);

		std::map<size_t, Equation> result;
		result.insert({ unknown, solution });

		return result;
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