#pragma once
#include <vector>
#include <string>

namespace EuchreNames
{

	std::string GetSuitName(int i);
	std::string GetValueName(int i);
}

class Card
{
public:
	int suit;
	int value;

	Card(int s, int v);
	std::string GetFullName();
};

