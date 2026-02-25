#pragma once
#include "System.h"

class SystemSimplifier
{
public:
	System Simplify(const System& system, const std::map<size_t, Equation>& solutions) const;
};

