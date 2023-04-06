#pragma once
#include <string>
#include "Deck.h"
#include "Player.h"

class Player;

class TrickData
{
public:
	TrickData();
	Card* highestCard;
	int trumpSuit;
	int trumpTeam;
	int highestTeam;
	int leadSuit;
	bool hasBeenTrumped;
};

class Game
{
private:
	void DealCardsToEachPlayer(int amount);
public:

	Deck gameDeck;
	vector<Player> players;
	int teamScores[2];

	Game();
	std::string Run();
	void Round();
	int Trick(int trumpSuit, int trumpTeam);
	void Reset();
	static int EvaluateCardScore(Card c, TrickData trick);
};

