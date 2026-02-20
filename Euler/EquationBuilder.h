#pragma once
#include "Equation.h"

class EquationBuilder
{
private:
	Equation equation;
	Product product;

public:
	EquationBuilder();

	void MultiplyByUnknown(char unknown);
	void FinishProduct(int scalar);

	Equation Create();
};

