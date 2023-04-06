#pragma once
#include "Card.h"

namespace EuchreNames
{
	std::string GetSuitName(int i)
	{
		switch (i)
		{
			case 0:
				return "Hearts";
			case 1:
				return "Diamonds";
			case 2:
				return "Clubs";
			case 3:
				return "Spades";
			default:
				return "Error";
		}
	}

	std::string GetValueName(int i)
	{
		switch (i)
		{
		case 8:
			return "Eight";
		case 9:
			return "Nine";
		case 10:
			return "Ten";
		case 11:
			return "Jack";
		case 12:
			return "Queen";
		case 13:
			return "King";
		case 14:
			return "Ace";
		default:
			return "Error";
		}
	}
}

Card::Card(int s, int v)
{
	suit = s;
	value = v;
}

std::string Card::GetFullName()
{
	return EuchreNames::GetValueName(value) + " of " + EuchreNames::GetSuitName(suit);
}