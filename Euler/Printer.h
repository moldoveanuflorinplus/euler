#pragma once
#include <string>
#include "Equation.h"
#include "System.h"

class Printer
{
public:
	std::string Print(const Product& product) const;
	std::string Print(const Equation& equation) const;
	std::string Print(const System& system) const;
};

