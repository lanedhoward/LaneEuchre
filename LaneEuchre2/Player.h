#pragma once
#include "Deck.h"
#include "Game.h"

class TrickData;

class Player
{
private:
	Deck* m_deck;
	vector<Card> m_hand;

public:
	int team;
	Player();
	void Initialize(Deck* deck, int team);
	void Reset();
	void AddToHand(Card c);
	bool AcceptTheTrump(Card c);
	Card PlayCard(TrickData trick);
};

