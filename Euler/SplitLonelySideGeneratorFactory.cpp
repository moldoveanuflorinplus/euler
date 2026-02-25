#include <algorithm>
#include <unordered_set>
#include "SplitLonelySideGeneratorFactory.h"
#include "SplitSolutionGenerator.h"

bool HasPositiveScalar(const std::pair<Product, int> product)
{
	return product.second > 0;
}

bool HasNegativeScalar(const std::pair<Product, int> product)
{
	return product.second < 0;
}

bool HasLonelyPositiveSide(const Equation & equation)
{
	const std::map<Product, int>& members = equation.GetMembers();
	return std::count_if(members.begin(), members.end(), HasPositiveScalar) == 1;
}

bool HasLonelyNegativeSide(const Equation & equation)
{
	const std::map<Product, int>& members = equation.GetMembers();
	return std::count_if(members.begin(), members.end(), HasNegativeScalar) == 1;
}

void InsertUnknowns(const Product & product, std::unordered_set<size_t>&unknowns)
{
	for (size_t i = 0; i < product.GetSize(); ++i)
	{
		if (product.GetPower(i) != 0)
		{
			unknowns.insert(i);
		}
	}
}

void InsertPositiveUnknowns(const Equation & equation, std::unordered_set<size_t>&unknowns)
{
	const std::map<Product, int>& members = equation.GetMembers();
	for (std::map<Product, int>::const_iterator m = members.begin(); m != members.end(); ++m)
	{
		if (HasPositiveScalar(*m))
		{
			InsertUnknowns(m->first, unknowns);
		}
	}
}

void InsertNegativeUnknowns(const Equation & equation, std::unordered_set<size_t>&unknowns)
{
	const std::map<Product, int>& members = equation.GetMembers();
	for (std::map<Product, int>::const_iterator m = members.begin(); m != members.end(); ++m)
	{
		if (HasNegativeScalar(*m))
		{
			InsertUnknowns(m->first, unknowns);
		}
	}
}

size_t GetNextUnknown(const Product & product)
{
	return product.GetSize();
}

size_t GetNextUnknown(const Equation & equation)
{
	const std::map<Product, int>& members = equation.GetMembers();
	size_t lastUnknown = 0;

	for (std::map<Product, int>::const_iterator it = members.begin(); it != members.end(); ++it)
	{
		lastUnknown = std::max(lastUnknown, GetNextUnknown(it->first));
	}

	return lastUnknown;
}

size_t GetNextUnknown(const System & system)
{
	const std::vector<Equation>& equalities = system.GetEqualities();
	size_t lastUnknown = 0;

	for (std::vector<Equation>::const_iterator it = equalities.begin(); it != equalities.end(); ++it)
	{
		lastUnknown = std::max(lastUnknown, GetNextUnknown(*it));
	}

	return lastUnknown;
}

Equation GenerateSplitEquation(const System & system)
{
	size_t next1 = GetNextUnknown(system);
	size_t next2 = next1 + 1;

	Product product1;
	product1.SetPower(next1, 1);

	Product product2;
	product2.SetPower(next2, 1);

	Equation result;
	result.Add(product1, 1);
	result.Add(product2, 1);

	return result;
}


std::shared_ptr<ISolutionGenerator> SplitLonelySideGeneratorFactory::Create(const System& system) const
{
	const std::vector<Equation>& equalities = system.GetEqualities();
	std::unordered_set<size_t> unknowns;

	for (std::vector<Equation>::const_iterator it = equalities.begin(); it != equalities.end(); ++it)
	{
		if (HasLonelyPositiveSide(*it))
		{
			InsertPositiveUnknowns(*it, unknowns);
		}
		if (HasLonelyNegativeSide(*it))
		{
			InsertNegativeUnknowns(*it, unknowns);
		}
	}

	Equation replacement = GenerateSplitEquation(system);

	return std::make_shared<SplitSolutionGenerator>(unknowns, unknowns.begin(), replacement);
}
