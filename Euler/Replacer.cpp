#include "Replacer.h"
#include <algorithm>
#include "EquationSolver.h"

size_t GetBiggestPower(const Equation& equation, const size_t unknown)
{
	size_t biggestPower = 0;
	std::map<Product, int> members = equation.GetMembers();

	for (auto it = members.begin(); it != members.end(); ++it)
	{
		biggestPower = std::max(it->first.GetPower(unknown), biggestPower);
	}
	return biggestPower;
}

std::vector<Equation> GetPowers(size_t power, const size_t unknown, const Equation& value)
{
	EquationSolver solver;
	std::vector<Equation> powers(power + 1);

	powers[0] = Equation::One();

	for (size_t i = 1, previous = 0; i < powers.size(); ++i, ++previous)
	{
		powers[i] = solver.Multiply(powers[previous], value);
	}

	return powers;
}

Equation Replacer::Replace(const Equation& equation, const size_t unknown, const Equation& value)
{
	EquationSolver solver;
	size_t biggestPower = GetBiggestPower(equation, unknown);
	
	std::vector<Equation> powers = GetPowers(biggestPower, unknown, value);

	Equation result;
	std::map<Product, int> members = equation.GetMembers();
	for (auto it = members.begin(); it != members.end(); ++it)
	{
		size_t power = it->first.GetPower(unknown);
		Product product = it->first;
		product.SetPower(unknown, 0);

		Equation partialResult = solver.Multiply(it->second, product, powers[power]);

		solver.Add(result, partialResult);
	}

	return result;
}
