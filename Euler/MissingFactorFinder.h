#pragma once

#include <utility>

#include "Equation.h"
#include "Product.h"
#include "System.h"

class MissingFactorFinder
{
private:
	std::pair<Product, int>& factor;
	std::pair<Product, int>& unFactored;


public:
	MissingFactorFinder(std::pair<Product, int>& factor, std::pair<Product, int>& unFactored);
	
	bool operator()(const Equation& equation);
};

