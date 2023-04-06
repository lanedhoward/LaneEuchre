#include "Player.h"

Player::Player()
{
	m_hand = vector<Card>();
}

void Player::Initialize(Deck* _deck, int _team)
{
	m_deck = _deck;
	team = _team;
	Reset();
}

void Player::Reset()
{
	m_hand.clear();
}

void Player::AddToHand(Card c)
{
	m_hand.push_back(c);
}

bool Player::AcceptTheTrump(Card c)
{
	int trumpCardsInHand = 0;

	for (size_t i = 0; i < m_hand.size(); i++)
	{
		Card current = m_hand[i];

		if (current.suit == c.suit ||
			(current.value == 11 && ((current.suit < 2) == (c.suit < 2)))) // checking for lesser trump jack
		{
			trumpCardsInHand++;
		}
	}

	if (trumpCardsInHand >= 2)
	{
		// we want the trump
		return true;
	}
	return false;
}

Card Player::PlayCard(TrickData trick)
{

	int highestCardValue = -1000;
	if (trick.highestCard != NULL)
	{
		highestCardValue = Game::EvaluateCardScore(*trick.highestCard, trick);
	}
	bool myTeamWinning = trick.highestTeam == this->team;

	int firstCardValue = Game::EvaluateCardScore(m_hand[0], trick);

	int myHighestCardValue = firstCardValue;
	int myHighestCardIndex = 0;
	Card* myHighestCard = &m_hand[0];
	int myLowestCardValue = firstCardValue;
	int myLowestCardIndex = 0;
	Card* myLowestCard = &m_hand[0];

	for (size_t i = 1; i < m_hand.size(); i++)
	{
		Card* current = &m_hand[i];

		int currentCardValue = Game::EvaluateCardScore(*current, trick);

		if (currentCardValue > myHighestCardValue)
		{
			myHighestCard = current;
			myHighestCardValue = currentCardValue;
			myHighestCardIndex = i;
		}

		if (currentCardValue < myLowestCardValue)
		{
			/*
			if (myLowestCard != nullptr)
			{
				if (current.value > myLowestCard->value)
				{
					continue;
				}
			}
			*/
			myLowestCard = current;
			myLowestCardValue = currentCardValue;
			myLowestCardIndex = i;
		}
	}

	if (!myTeamWinning)
	{
		m_hand.erase(m_hand.begin() + myHighestCardIndex);
		return *myHighestCard;
	}
	m_hand.erase(m_hand.begin() + myLowestCardIndex);
	return *myLowestCard;

}