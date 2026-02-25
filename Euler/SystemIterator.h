#pragma once
#include <memory>
#include "System.h"
#include "ISolutionGenerator.h"

class SystemIterator
{
private:
	System system;
	std::shared_ptr<ISolutionGenerator> generator;

public:
	SystemIterator(const std::shared_ptr<ISolutionGenerator>& generator, const System& system);

	const System& GetSystem() const;
	ISolutionGenerator* GetGenerator();

	bool IsValid() const;
};

