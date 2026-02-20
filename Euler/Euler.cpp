
#include <iostream>
#include "EquationBuilder.h"
#include "Printer.h"
#include "Solver.h"
#include "Replacer.h"

void SimpleTest()
{
	EquationBuilder builder;

	builder.MultiplyByUnknown('a');
	builder.FinishProduct(2);

	builder.MultiplyByUnknown('a');
	builder.MultiplyByUnknown('a');
	builder.FinishProduct(1);

	builder.MultiplyByUnknown('b');
	builder.FinishProduct(-3);

	Equation left = builder.Create();

	builder.FinishProduct(10);
	builder.MultiplyByUnknown('a');
	builder.MultiplyByUnknown('c');
	builder.FinishProduct(2);

	Equation right = builder.Create();

	Solver solver;
	Equation result = solver.Multiply(left, right);

	Printer printer;
	std::cout << printer.Print(left).c_str() << std::endl;
	std::cout << printer.Print(right).c_str() << std::endl;
	std::cout << printer.Print(result).c_str() << std::endl;
}

void SimplifierTest()
{
	EquationBuilder builder;

	builder.MultiplyByUnknown('a');
	builder.FinishProduct(3);
	builder.FinishProduct(5);

	Equation left = builder.Create();

	builder.MultiplyByUnknown('a');
	builder.FinishProduct(7);
	builder.FinishProduct(11);

	Equation right = builder.Create();

	Solver solver;
	Equation result = solver.Multiply(left, right);

	Printer printer;
	std::cout << printer.Print(left).c_str() << std::endl;
	std::cout << printer.Print(right).c_str() << std::endl;
	std::cout << printer.Print(result).c_str() << std::endl;
}

void ReplacerTest()
{
	EquationBuilder builder;

	builder.MultiplyByUnknown('a');
	builder.MultiplyByUnknown('a');
	builder.FinishProduct(1);
	builder.MultiplyByUnknown('a');
	builder.FinishProduct(10);

	Equation left = builder.Create();

	builder.MultiplyByUnknown('b');
	builder.FinishProduct(1);
	builder.FinishProduct(1);

	Equation right = builder.Create();

	Replacer replacer;
	Equation result = replacer.Replace(left, 0, right);

	Printer printer;
	std::cout << printer.Print(left).c_str() << std::endl;
	std::cout << printer.Print(right).c_str() << std::endl;
	std::cout << printer.Print(result).c_str() << std::endl;
}


int main()
{
	ReplacerTest();
}