#include "Printer.h"

std::string PrintFirstValue(int scalar)
{
	return std::to_string(scalar);
}

std::string PrintFirstScalar(int scalar)
{
	if (scalar == 1)
	{
		return "";
	}
	if (scalar == -1)
	{
		return "-";
	}
	return PrintFirstValue(scalar);
}

std::string PrintValue(int scalar)
{
	if (scalar < 0)
	{
		return std::to_string(scalar);
	}
	return "+" + std::to_string(scalar);
}

std::string PrintScalar(int scalar)
{
	if (scalar == 1)
	{
		return "+";
	}
	if (scalar == -1)
	{
		return "-";
	}
	return PrintValue(scalar);
}

std::string Printer::Print(const Equation& equation) const
{
	std::string result = "";
	const std::map<Product, int> members = equation.GetMembers();
	std::map<Product, int>::const_iterator it = members.begin();

	if (members.begin() == members.end())
	{
		return "0";
	}

	if (it->first.GetSize() > 0)
	{
		result += PrintFirstScalar(it->second);
		result += Print(it->first);
	}
	else
	{
		result += PrintFirstValue(it->second);
	}

	for (++it; it != members.end(); ++it)
	{
		if (it->first.GetSize() > 0)
		{
			result += PrintScalar(it->second);
			result += Print(it->first);
		}
		else
		{
			result += PrintValue(it->second);
		}
	}

	return result;
}

std::string UnknownLabel(size_t unknown)
{
	return std::string(1, ('a' + unknown));
}

std::string PrintUnknown(size_t unknown, unsigned int power)
{
	if (power == 0)
	{
		return "";
	}
	if (power == 1)
	{
		return UnknownLabel(unknown);
	}
	return "(" + UnknownLabel(unknown) + ")^(" + std::to_string(power) + ")";
}

std::string Printer::Print(const Product& product) const
{
	std::string result = "";
	for (size_t i = 0; i < product.GetSize(); ++i)
	{
		result += PrintUnknown(i, product.GetPower(i));
	}
	return result;
}

std::string Printer::Print(const System& system) const
{
	std::string result = "";

	const std::vector<Equation> equalities = system.GetEqualities();
	for (std::vector<Equation>::const_iterator it = equalities.begin(); it != equalities.end(); ++it)
	{
		result += Print(*it) + " = 0\n";
	}

	const std::vector<Equation> solutions = system.GetSolutions();
	for (size_t i = 0; i < solutions.size(); ++i)
	{
		result += std::string(1, 'a'+ i) + " = " + Print(solutions.at(i)) + "\n";
	}

	return result;
}