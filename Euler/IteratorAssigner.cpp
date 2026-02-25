#include "IteratorAssigner.h"
#include "SplitLonelySideGeneratorFactory.h"

SystemIterator IteratorAssigner::Assign(System& system) const
{
	SplitLonelySideGeneratorFactory iteratorFactory;
	std::shared_ptr<ISolutionGenerator> generator = iteratorFactory.Create(system);

	SystemIterator iterator(generator, system);

	return iterator;
}
