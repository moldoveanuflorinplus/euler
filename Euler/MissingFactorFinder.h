#pragma once

#include <utility>

#include "Equation.h"
#include "Product.h"
#include "System.h"

class MissingFactorFinder
{
private:
	std::pair<Product, int> factor;
	std::pair<Product, int> unFactored;


public:

	std::pair<Product, int> GetFactor() const;
	std::pair<Product, int> GetUnFactored() const;
	
	bool operator()(const Equation& equation);
};

