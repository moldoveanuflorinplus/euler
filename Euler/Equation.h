#pragma once
#include <vector>
#include "Product.h"

class Equation
{
private:
	std::vector<Product> members;
public:
	Equation();
	Equation(size_t amount);

	void Add(const Product& member);

	size_t GetSize() const;
	Product& GetMember(size_t index);
	const Product& GetMember(size_t index) const;
};

