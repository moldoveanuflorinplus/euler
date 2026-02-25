#pragma once
#include <vector>
#include "System.h"
#include "SystemIterator.h"

class SystemSolver
{
public:
	void Next(std::vector<SystemIterator>& collection);
};

