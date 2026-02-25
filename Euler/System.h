#pragma once
#include <vector>
#include "Equation.h"

class System
{
private:
	std::vector<Equation> solutions;
	std::vector<Equation> equalities;

public:

	void AddEquality(const Equation& equality);
	void AddSolution(const Equation& equation);

	const std::vector<Equation>& GetEqualities() const;
	const std::vector<Equation>& GetSolutions() const;
};

