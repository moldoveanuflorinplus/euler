#include "System.h"

void System::AddEquality(const Equation& equality)
{
	if (equality.GetMembers().size() > 0)
	{
		equalities.push_back(equality);
	}
}

void System::AddSolution(const Equation & equation)
{
	solutions.push_back(equation);
}

const std::vector<Equation>& System::GetEqualities() const
{
	return equalities;
}

const std::vector<Equation>& System::GetSolutions() const
{
	return solutions;
}
