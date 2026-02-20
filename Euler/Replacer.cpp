#include "Replacer.h"
#include <algorithm>
#include "Solver.h"

unsigned int GetBiggestPower(const Equation& equation, const size_t unknown)
{
	unsigned int biggestPower = 0;
	std::map<Product, int> members = equation.GetMembers();

	for (auto it = members.begin(); it != members.end(); ++it)
	{
		biggestPower = std::max(it->first.GetPower(unknown), biggestPower);
	}
	return biggestPower;
}

std::vector<Equation> GetPowers(int power, const size_t unknown, const Equation& value)
{
	Solver solver;
	std::vector<Equation> powers(power + 1);

	powers[0] = Equation::One();

	for (auto i = 1; i < powers.size(); ++i)
	{
		powers[i] = solver.Multiply(powers[i - 1], value);
	}

	return powers;
}

Equation Replacer::Replace(const Equation& equation, const size_t unknown, const Equation& value)
{
	Solver solver;
	unsigned int biggestPower = GetBiggestPower(equation, unknown);
	
	std::vector<Equation> powers = GetPowers(biggestPower, unknown, value);

	Equation result;
	std::map<Product, int> members = equation.GetMembers();
	for (auto it = members.begin(); it != members.end(); ++it)
	{
		unsigned int power = it->first.GetPower(unknown);
		Product product = it->first;
		product.SetPower(unknown, 0);

		Equation partialResult = solver.Multiply(it->second, product, powers[power]);

		solver.Add(result, partialResult);
	}

	return result;
}
