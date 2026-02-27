#include "EquationAnalizer.h"

size_t GetNext(const Product& product)
{
	return product.GetSize();
}

bool CompareNextUnknown(const std::pair<Product, size_t>& a, const std::pair<Product, size_t>& b)
{
	return GetNext(a.first) < GetNext(b.first);
}

size_t GetNext(const Equation& equation)
{
	const std::map<Product, int>& members = equation.GetMembers();
	const std::map<Product, int>::const_iterator it = std::max_element(members.begin(), members.end(), CompareNextUnknown);
	return GetNext(it->first);
}

size_t EquationAnalizer::GetNextUnknown(const System& system) const
{
	const std::vector<Equation>& equalities = system.GetEqualities();
	size_t lastUnknown = 0U;

	for (std::vector<Equation>::const_iterator it = equalities.begin(); it != equalities.end(); ++it)
	{
		lastUnknown = std::max(lastUnknown, GetNext(*it));
	}

	return lastUnknown;
}

std::vector<size_t> EquationAnalizer::GetUnknowns(const std::vector<size_t>& product) const
{
	std::vector<size_t> result;

	for (size_t i = 0; i < product.size(); ++i)
	{
		if (product.at(i) > 0)
		{
			result.push_back(i);
		}
	}
	return result;
}

std::vector<size_t> EquationAnalizer::GetUnknowns(const Product& product) const
{
	return GetUnknowns(product.GetPowers());
}