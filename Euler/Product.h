#pragma once
#include <vector>

class Product
{
private:
	std::vector<unsigned int> powers;

public:
	Product();

	void SetPower(size_t unknown, unsigned int power);

	size_t GetSize() const;
	unsigned int GetPower(size_t unknown) const;

	bool operator<(const Product& other) const;
};

