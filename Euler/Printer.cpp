#include "Printer.h"

std::string Printer::Print(const Equation& equation) const
{
	std::string result = "";
	result += Print(equation.GetMember(0));

	for (size_t i = 1; i < equation.GetSize(); ++i)
	{
		const Product& product = equation.GetMember(i);
		if (product.GetScalar() > 0)
		{
			result += "+";
		}
		result += Print(product);
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

std::string PrintScalar(int scalar)
{
	if (scalar == 1)
	{
		return "";
	}
	if (scalar == -1)
	{
		return "-";
	}
	return std::to_string(scalar);
}

std::string Printer::Print(const Product& product) const
{
	std::string result = "";
	result += PrintScalar(product.GetScalar());
	for (size_t i = 0; i < product.GetSize(); ++i)
	{
		result += PrintUnknown(i, product.GetPower(i));
	}
	return result;
}