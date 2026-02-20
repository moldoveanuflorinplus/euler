#include "EquationBuilder.h"

EquationBuilder::EquationBuilder() :
	equation(),
	product()
{
}

void EquationBuilder::FinishProduct(int scalar)
{
	equation.Add(product, scalar);
	product = Product();
}

void EquationBuilder::MultiplyByUnknown(char unknown)
{
	unsigned int index = unknown - 'a';
	product.SetPower(index, product.GetPower(index) + 1);
}

Equation EquationBuilder::Create()
{
	Equation result = equation;
	equation = Equation();
	return result;
}