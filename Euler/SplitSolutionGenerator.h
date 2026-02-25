#pragma once
#include <unordered_set>
#include "ISolutionGenerator.h"

class SplitSolutionGenerator : public ISolutionGenerator
{
private:
	std::unordered_set<size_t> unknowns;
	std::unordered_set<size_t>::iterator unknownIt;
	Equation replacement;

public:
	SplitSolutionGenerator(
		std::unordered_set<size_t> unknowns,
		std::unordered_set<size_t>::iterator unknownIt,
		Equation replacement);

	virtual std::map<size_t, Equation> NextSolutions();
	virtual bool IsFinished() const;
};

