#pragma once
#include <vector>

class Product
{
private:
	std::vector<size_t> powers;

public:
	Product();

	void SetPower(size_t unknown, size_t power);

	size_t GetSize() const;
	size_t GetPower(size_t unknown) const;
	const std::vector<size_t>& GetPowers() const;

	bool operator<(const Product& other) const;
};

