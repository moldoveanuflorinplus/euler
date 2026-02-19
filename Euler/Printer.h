#pragma once
#include <string>
#include "Equation.h"

class Printer
{
public:
	std::string Print(const Equation& equation) const;

	std::string Print(const Product& product) const;
};

