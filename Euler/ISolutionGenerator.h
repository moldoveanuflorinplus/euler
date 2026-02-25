#pragma once

#include <map>
#include "System.h"

class ISolutionGenerator
{
public:
	virtual ~ISolutionGenerator() = default;

	virtual std::map<size_t, Equation> NextSolutions() = 0;
	virtual bool IsFinished() const = 0;
};

