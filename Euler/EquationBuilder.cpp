#include "EquationBuilder.h"

EquationBuilder::EquationBuilder() :
	equation(),
	product()
{
}

void EquationBuilder::MultiplyByScalar(int scalar)
{
	product.SetScalar(product.GetScalar() * scalar);
}

void EquationBuilder::MultiplyByUnknown(char unknown)
{
	unsigned int index = unknown - 'a';
	product.SetPower(index, product.GetPower(index) + 1);
}

void EquationBuilder::Plus()
{
	equation.Add(product);
	product = Product(1);
}

Equation EquationBuilder::Create()
{
	if (product.GetSize() > 0)
	{
		Plus();
	}
	Equation result = equation;
	equation = Equation();
	return result;
}