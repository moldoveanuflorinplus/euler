#pragma once
#include <memory>
#include "ISolutionGenerator.h"

class ISolutionGeneratorFactory
{
public:
	virtual std::shared_ptr<ISolutionGenerator> Create(const System& system) const = 0;
};

