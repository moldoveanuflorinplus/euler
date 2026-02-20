#pragma once
#include "Equation.h"

class Solver
{
public:
	void Add(Equation& result, const Equation& addition) const;
	Equation Multiply(const Equation& left, const Equation& right) const;
	Equation Multiply(int scalar, const Product& left, const Equation& right) const;
};

