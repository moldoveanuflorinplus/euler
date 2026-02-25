#include <algorithm>
#include "SplitSolutionGenerator.h"

SplitSolutionGenerator::SplitSolutionGenerator(
	std::unordered_set<size_t> unknowns,
	std::unordered_set<size_t>::iterator unknownIt,
	Equation replacement)
	: unknowns(unknowns)
	, unknownIt(unknownIt)
	, replacement(replacement)
{
}

std::map<size_t, Equation> GenerateSolution(const size_t unknown, const Equation& replacement)
{
	std::map<size_t, Equation> result;

	result.insert({ unknown, replacement });

	return result;
}

std::map<size_t, Equation> SplitSolutionGenerator::NextSolutions()
{
	std::map<size_t, Equation> solution = GenerateSolution(*unknownIt, replacement);
	++unknownIt;

	return solution;
}

bool SplitSolutionGenerator::IsFinished() const
{
	return unknownIt == unknowns.end();
}