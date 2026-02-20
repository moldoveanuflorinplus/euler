#pragma once
#include <map>
#include "Product.h"

class Equation
{
private:
	std::map<Product, int> members;
public:
	Equation();

	void Add(const Product& key, int scalar);

	const std::map<Product, int> GetMembers() const;
};

