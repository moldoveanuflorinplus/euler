
#include <iostream>
#include "EquationBuilder.h"
#include "EquationSolver.h"
#include "Printer.h"
#include "Replacer.h"
#include "System.h"
#include "SystemSimplifier.h"

size_t ToIndex(char letter)
{
	return letter - 'a';
}

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

	EquationSolver solver;
	Equation result = solver.Multiply(left, right);

	Printer printer;
	std::cout << "Simple test" << std::endl;
	std::cout << printer.Print(left).c_str() << std::endl;
	std::cout << printer.Print(right).c_str() << std::endl;
	std::cout << printer.Print(result).c_str() << std::endl;
	std::cout << std::endl;
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

	EquationSolver solver;
	Equation result = solver.Multiply(left, right);

	Printer printer;
	std::cout << "Simplifier test" << std::endl;
	std::cout << printer.Print(left).c_str() << std::endl;
	std::cout << printer.Print(right).c_str() << std::endl;
	std::cout << printer.Print(result).c_str() << std::endl;
	std::cout << std::endl;
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
	std::cout << "Replacer test" << std::endl;
	std::cout << printer.Print(left).c_str() << std::endl;
	std::cout << printer.Print(right).c_str() << std::endl;
	std::cout << printer.Print(result).c_str() << std::endl;
	std::cout << std::endl;
}

void SystemReplacerTest()
{
	System system;

	EquationBuilder builder;

	builder.MultiplyByUnknown('a');
	builder.MultiplyByUnknown('a');
	builder.FinishProduct(1);
	builder.MultiplyByUnknown('b');
	builder.MultiplyByUnknown('b');
	builder.FinishProduct(1);
	builder.MultiplyByUnknown('c');
	builder.MultiplyByUnknown('c');
	builder.FinishProduct(-1);

	system.AddEquality(builder.Create());

	builder.MultiplyByUnknown('a');
	builder.FinishProduct(1);
	system.AddSolution(builder.Create());

	builder.MultiplyByUnknown('b');
	builder.FinishProduct(1);
	system.AddSolution(builder.Create());

	builder.MultiplyByUnknown('c');
	builder.FinishProduct(1);
	system.AddSolution(builder.Create());

	std::cout << "System Replacer test" << std::endl;

	SystemSimplifier replacer;
	Printer printer;
	std::cout << printer.Print(system).c_str();
	std::cout << std::endl;

	// Step 1
	{
		std::map<size_t, Equation> solutions;

		builder.MultiplyByUnknown('d');
		builder.FinishProduct(1);
		builder.MultiplyByUnknown('e');
		builder.FinishProduct(1);
		solutions.insert({ ToIndex('c'), builder.Create()});

		system = replacer.Simplify(system, solutions);

		std::cout << printer.Print(system).c_str();
		std::cout << std::endl;
	}
	
	// Step 2
	{
		std::map<size_t, Equation> solutions;

		builder.MultiplyByUnknown('d');
		builder.FinishProduct(1);
		solutions.insert({ ToIndex('a'), builder.Create() });

		system = replacer.Simplify(system, solutions);

		std::cout << printer.Print(system).c_str();
		std::cout << std::endl;
	}

	// Step 3
	{
		std::map<size_t, Equation> solutions;
	
		builder.MultiplyByUnknown('g');
		builder.MultiplyByUnknown('h');
		builder.MultiplyByUnknown('i');
		builder.FinishProduct(1);
		solutions.insert({ ToIndex('b'), builder.Create() });
	
		builder.MultiplyByUnknown('g');
		builder.MultiplyByUnknown('g');
		builder.MultiplyByUnknown('h');
		builder.FinishProduct(1);
		solutions.insert({ ToIndex('e'), builder.Create() });
	
		builder.MultiplyByUnknown('h');
		builder.MultiplyByUnknown('i');
		builder.MultiplyByUnknown('i');
		builder.FinishProduct(1);
		solutions.insert({ ToIndex('f'), builder.Create() });
	
		system = replacer.Simplify(system, solutions);
	
		std::cout << printer.Print(system).c_str();
		std::cout << std::endl;
	}

	// Step 4
	{
		std::map<size_t, Equation> solutions;
	
		builder.MultiplyByUnknown('i');
		builder.FinishProduct(2);
		solutions.insert({ ToIndex('f'), builder.Create() });

		builder.MultiplyByUnknown('i');
		builder.MultiplyByUnknown('h');
		builder.FinishProduct(1);
		solutions.insert({ ToIndex('d'), builder.Create() });

		system = replacer.Simplify(system, solutions);
	
		std::cout << printer.Print(system).c_str();
		std::cout << std::endl;
	}

	// Step 5
	{
		std::map<size_t, Equation> solutions;
	
		builder.MultiplyByUnknown('h');
		builder.FinishProduct(1);
		builder.MultiplyByUnknown('i');
		builder.FinishProduct(1);
		solutions.insert({ ToIndex('e'), builder.Create() });
	
		system = replacer.Simplify(system, solutions);
	
		std::cout << printer.Print(system).c_str();
		std::cout << std::endl;
	}

	// Step 5
	{
		std::map<size_t, Equation> solutions;

		builder.MultiplyByUnknown('d');
		builder.FinishProduct(1);
		solutions.insert({ ToIndex('g'), builder.Create() });

		system = replacer.Simplify(system, solutions);

		std::cout << printer.Print(system).c_str();
		std::cout << std::endl;
	}
}

int main()
{
	SimpleTest();
	SimplifierTest();
	ReplacerTest();
	SystemReplacerTest();
}