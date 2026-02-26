#pragma once
#include "System.h"

class EquationAnalizer
{
public:
	size_t GetNextUnknown(const System& system) const;
	std::vector<size_t> GetUnknowns(const Product& product) const;
	std::vector<size_t> GetUnknowns(const std::vector<size_t>& product) const;
};

