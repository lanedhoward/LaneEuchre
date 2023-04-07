#include "Game.h"
#include "Deck.h"
#include "ConsoleUtils.h"

using namespace ConsoleUtils;

Game::Game()
{
	gameDeck = Deck();
	players = vector<Player>();

	for (size_t i = 1; i <= 4; i++)
	{
		int team = i % 2; //0 or 1
		Player p = Player();
		p.Initialize(&gameDeck, team);
		players.push_back(p);
	}

}

std::string Game::Run()
{
	teamScores[0] = 0;
	teamScores[1] = 0;

	const size_t MAX_ROUNDS = 50;

	for (size_t i = 0; i < MAX_ROUNDS; i++)
	{
		Round();

		Print("Scores:  Team 0: " + std::to_string(teamScores[0]) + " / Team 1: " + std::to_string(teamScores[1]));

		if (teamScores[0] >= 10 || teamScores[1] >= 10)
		{
			// winner!
			int gameWinningTeam = 0;
			if (teamScores[1] > teamScores[0])
			{
				gameWinningTeam = 1;
			}

			Print("Winner!! Team " + std::to_string(gameWinningTeam) + " has won!!! ");
			WaitForKeyPress();

			break;
		}
		WaitForKeyPress();
	}

	return "";
}

void Game::Round()
{
	Reset();
	// deal
	DealCardsToEachPlayer(2);
	DealCardsToEachPlayer(3);

	// determine trump suit
	Card potentialTrump = *gameDeck.Draw();

	bool acceptedTrump = false;
	// might need to make these instance vars instead of local vars
	int trumpSuit;
	int trumpTeam;

	for (size_t i = 0; i < players.size(); i++)
	{
		Player p = players[i];

		if (p.AcceptTheTrump(potentialTrump))
		{
			acceptedTrump = true;
			trumpSuit = potentialTrump.suit;
			trumpTeam = p.team;
			break;
		}
	}

	if (acceptedTrump == false)
	{
		// no trump accepted, just start a new round over
		// as per karl's instructions
		return Round();
	}

	int trickWins[2];

	trickWins[0] = 0;
	trickWins[1] = 0;

	// actual trick play begins
	for (size_t i = 0; i < 5; i++)
	{

		int winningTeam = Trick(trumpSuit, trumpTeam);
		trickWins[winningTeam] += 1;
	}
	
	int handWinningTeam = 0;
	if (trickWins[1] > trickWins[0])
	{
		handWinningTeam = 1;
	}

	teamScores[handWinningTeam] += 1;

	if (handWinningTeam != trumpTeam)
	{
		teamScores[trumpTeam] -= 1;
	}

}

int Game::Trick(int trumpSuit, int trumpTeam)
{
	TrickData trick = TrickData();
	trick.trumpSuit = trumpSuit;
	trick.trumpTeam = trumpTeam;
	
	Print("New Trick. Trump is " + EuchreNames::GetSuitName(trumpSuit));

	for (size_t i = 0; i < players.size(); i++)
	{
		Player* p = &players[i];
		Card* playedCard = p->PlayCard(trick);

		if (trick.highestCard == nullptr)
		{
			// first player
			trick.highestCard = playedCard;
			trick.highestTeam = p->team;
			trick.leadSuit = playedCard->suit;
		}
		else
		{
			//compare played card to the current trick
			if (EvaluateCardScore(*trick.highestCard, trick) < EvaluateCardScore(*playedCard, trick))
			{
				trick.highestCard = playedCard;
				trick.highestTeam = p->team;

				if (trick.trumpSuit == playedCard->suit ||
					(playedCard->value == 11 && ((trick.trumpSuit < 2) == (playedCard->suit < 2)))) // checking for lesser trump jack
				{
					trick.hasBeenTrumped = true;
				}

			}
		}
		Print("    Player " + std::to_string(i) + " (Team " + std::to_string(p->team) + ") played " + playedCard->GetFullName());
	}

	Print("Trick complete. \n    Trump Suit: " + EuchreNames::GetSuitName(trick.trumpSuit) + " \n    Lead Suit: " + EuchreNames::GetSuitName(trick.leadSuit) + " \n    Trump team: " + std::to_string(trick.trumpTeam) + " \n    Highest Card: " + trick.highestCard->GetFullName() + " \n    Winning Team: " + std::to_string(trick.highestTeam));

	return trick.highestTeam;
}

void Game::Reset()
{
	// reset deck and players
	gameDeck.Reset();
	for (size_t i = 0; i < players.size(); i++)
	{
		players[i].Reset();
	}


}

void Game::DealCardsToEachPlayer(int amount)
{
	for (size_t i = 0; i < players.size(); i++)
	{
		for (size_t j = 0; j < amount; j++)
		{
			players[i].AddToHand(gameDeck.Draw());
		}
	}
}


TrickData::TrickData()
{
	Card* highestCard = nullptr;
	int trumpSuit = -1;
	int trumpTeam = -1;
	int highestTeam = -1;
	int leadSuit = -1;
	hasBeenTrumped = false;
}

int Game::EvaluateCardScore(Card c, TrickData trick)
{
	int score = 0;

	if (c.suit == trick.leadSuit)
	{
		score = c.value;
	}

	if (c.suit == trick.trumpSuit)
	{
		score = c.value * 2;
	}

	if (c.value == 11)
	{
		if (c.suit == trick.trumpSuit)
		{
			// trump jack
			score = 100;
		}
		else if ((trick.trumpSuit < 2) == (c.suit < 2))
		{
			//lesser jack
			score = 75;
		}
	}

	return score;
}