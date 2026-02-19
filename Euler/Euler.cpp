
#include <iostream>
#include "EquationBuilder.h"
#include "Printer.h"
#include "Solver.h"

int main()
{
	EquationBuilder builder;

	builder.MultiplyByScalar(2);
	builder.MultiplyByUnknown('a');
	builder.Plus();
	builder.MultiplyByUnknown('a');
	builder.MultiplyByUnknown('a');
	builder.Plus();
	builder.MultiplyByScalar(-3);
	builder.MultiplyByUnknown('b');
	
	Equation left = builder.Create();

	builder.MultiplyByScalar(10);
	builder.Plus();
	builder.MultiplyByScalar(2);
	builder.MultiplyByUnknown('a');
	builder.MultiplyByUnknown('c');

	Equation right = builder.Create();

	Solver solver;
	Equation result = solver.Multiply(left, right);

	Printer printer;
	std::cout << printer.Print(left).c_str() << std::endl;
	std::cout << printer.Print(right).c_str() << std::endl;
	std::cout << printer.Print(result).c_str() << std::endl;
}