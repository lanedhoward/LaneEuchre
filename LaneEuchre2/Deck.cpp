#pragma once
#include "Deck.h"
#include <time.h>

Deck::Deck()
{
	//seed random number generator
	// taken from https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
	srand(time(0));

	Reset();
}

void Deck::Populate()
{
	// clears deck, fills it up with int "Cards" from 1-10. but 10 is added 3 more times for the face cards. repeats for 4 suits.
	deck.clear();
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 8; j <= 14; j++)
		{
			Card c = Card(i, j);
			deck.push_back(c);
		}
	}

}

void Deck::Shuffle()
{
	// knuth-fisher-yates shuffle adapted from https://blog.codinghorror.com/the-danger-of-naivete/
	for (size_t i = deck.size()-1; i > 0; i--)
	{
		int n = rand() % (i + 1);

		Card temp = deck[i];
		deck[i] = deck[n];
		deck[n] = temp;
	}
}

Card* Deck::Draw()
{
	Card* drawn = &deck.back();
	deck.pop_back();
	return drawn;
}

void Deck::Reset()
{
	Populate();
	Shuffle();
}