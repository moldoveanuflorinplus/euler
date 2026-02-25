#pragma once
#include "ISolutionGeneratorFactory.h"

class SplitLonelySideGeneratorFactory : public ISolutionGeneratorFactory
{
public:
	virtual std::shared_ptr<ISolutionGenerator> Create(const System& system) const;
};

