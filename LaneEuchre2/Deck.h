#pragma once
#include <vector>
#include "Card.h"

using namespace std;

class Deck
{
public:
	
	vector<Card> deck;

	Deck();
	void Populate();
	void Shuffle();
	Card Draw();
	void Reset();
};

