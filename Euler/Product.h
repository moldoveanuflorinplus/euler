#pragma once
#include <vector>

class Product
{
private:
	int scalar;
	std::vector<unsigned int> powers;

public:
	Product();
	Product(int scalar);

	void SetScalar(int scalar);
	void SetPower(size_t unknown, unsigned int power);

	int GetScalar() const;
	size_t GetSize() const;
	unsigned int GetPower(size_t unknown) const;
};

