#pragma once
#include <vector>

class PowerIterator
{
private:
	std::vector<size_t> max;
	std::vector<size_t> index;

public:
	PowerIterator(const std::vector<size_t>& max);

	bool Next();

	const std::vector<size_t>& GetIndex() const;
};

