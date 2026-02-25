#include "SystemIterator.h"

SystemIterator::SystemIterator(const std::shared_ptr<ISolutionGenerator>& generator, const System& system) :
	generator(generator),
	system(system)
{
}

const System& SystemIterator::GetSystem() const
{
	return system;
}

ISolutionGenerator* SystemIterator::GetGenerator()
{
	return generator.get();
}

bool SystemIterator::IsValid() const
{
	return true;
}