#include <algorithm>

#include "Replacer.h"
#include "SystemSolver.h"
#include "SystemSimplifier.h"
#include "IteratorAssigner.h"

std::vector<SystemIterator>::iterator SelectIterator(std::vector<SystemIterator>& collection)
{
	return --collection.end();
}

SystemIterator Advance(SystemIterator& iterator)
{
	ISolutionGenerator* generator = iterator.GetGenerator();
	std::map<size_t, Equation> solutions = generator->NextSolutions();
	
	SystemSimplifier simplifier;
	System result = simplifier.Simplify(iterator.GetSystem(), solutions);

	IteratorAssigner assigner;
	return assigner.Assign(result);
}

void SystemSolver::Next(std::vector<SystemIterator>& collection)
{
	std::vector<SystemIterator>::iterator iterator = SelectIterator(collection);
	SystemIterator next = Advance(*iterator);

	if (next.IsValid())
	{
		collection.push_back(next);
	}

	if (iterator->GetGenerator()->IsFinished())
	{
		collection.erase(iterator);
	}
}

