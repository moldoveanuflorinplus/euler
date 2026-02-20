#pragma once
#include "Equation.h"

class Replacer
{
public:
	Equation Replace(const Equation& equation, const size_t unknown, const Equation& value);
};

