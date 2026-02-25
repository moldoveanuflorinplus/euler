#include "SystemSimplifier.h"
#include "Replacer.h"

System Replace(const System& system, const size_t unknown, const Equation& solution)
{
	System result;

	std::vector<Equation> equalities = system.GetEqualities();
	for (std::vector<Equation>::const_iterator it = equalities.begin(); it != equalities.end(); ++it)
	{
		Replacer replacer;
		result.AddEquality(replacer.Replace(*it, unknown, solution));
	}

	std::vector<Equation> solutions = system.GetSolutions();
	for (std::vector<Equation>::const_iterator it = solutions.begin(); it != solutions.end(); ++it)
	{
		Replacer replacer;
		result.AddSolution(replacer.Replace(*it, unknown, solution));
	}

	return result;
}

System SystemSimplifier::Simplify(const System& system, const std::map<size_t, Equation>& solutions) const
{
	System result = system;
	for (std::map<size_t, Equation>::const_iterator it = solutions.begin(); it != solutions.end(); ++it)
	{
		result = Replace(result, it->first, it->second);
	}
	return result;
}