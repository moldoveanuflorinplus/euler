#pragma once
#include "Equation.h"

class EquationSolver
{
public:
	void Add(Equation& result, const Equation& addition) const;
	Equation Multiply(int scalar, const Equation& right) const;
	Equation Multiply(int scalar, const Product& left, const Equation& right) const;
	Equation Multiply(const Equation& left, const Equation& right) const;
	Equation Divide(const Equation& divident, const std::pair<Product, int>& divisor) const;
	std::pair<Product, int> Divide(const std::pair<Product, int>& divident, const std::pair<Product, int>& divisor) const;
	std::pair<Product, int> Factor(const std::pair<Product, int>& left, const std::pair<Product, int>& right) const;
	Product Factor(const Product& left, const Product& right) const;
};

