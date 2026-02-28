#pragma once
#include "Equation.h"

class SolutionFinder
{
private:
	Equation& found;
	size_t& unknown;
	int& scalar;

public:

	SolutionFinder(Equation& found, size_t& unknown, int& scalar);

	bool operator()(const Equation& equation);
};
