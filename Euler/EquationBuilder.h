#pragma once
#include "Equation.h"

class EquationBuilder
{
private:
	Equation equation;
	Product product;

public:
	EquationBuilder();

	void MultiplyByScalar(int scalar);
	void MultiplyByUnknown(char unknown);
	void Plus();
	Equation Create();
};

