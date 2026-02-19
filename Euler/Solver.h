#pragma once
#include "Equation.h"

class Solver
{
public:
	Equation Multiply(const Equation& left, const Equation& right) const;
};

