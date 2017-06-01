#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
static const int suits = 4;
static const int combinationsSize = 5;

enum PlayerType
{
	RealPlayer,
	CPU
};
enum Color
{
	Hearts,
	Diamonds,
	Clubs,
	Spades,
};
enum Value
{
	Jack = 11,
	Queen,
	King,
	Ace
};
enum HandCategories
{
	HighCard,
	OnePair,
	TwoPair,
	ThreeOfAKind,
	Straight,
	Flush,
	FullHouse,
	FourOfAKind,
	StraightFlush,
	RoyalFlush
};

enum Actions
{
	Fold,
	Check,
	Call,
	Bet,
	Raise,
	AllIn
};

enum PlayerPosition
{
	Dealer,
	SmallBlind
	BigBlind
};

class Card
{
public:
	Card(Value value = static_cast<Value>(1), Color color = Hearts)
		:value(value)
		,color(color)
	{
	}

	Value value;
	Color color;
};

bool operator <(const Card&, const Card&);
bool operator ==(const Card&, const Card&);
class Game;

class Player
{
public:
	Player()
	{
	}

	virtual void Play() = 0;
	HandCategories GetHandCategories() const;
protected:
	void Combination();
	friend class Round;
	friend class Game;
	int m_money;
	Card m_card1;
	Card m_card2;
	HandCategories m_handCategories = HighCard;
	Card* m_kicker1 = new Card(static_cast<Value>(1), Clubs);
	Card* m_kicker2 = new Card(static_cast<Value>(1), Spades);
	PlayerType m_playerType;
	bool m_dealer = false;
};

static const vector < pair < pair<Value, Value>, char >> preflopHandsVector = PreflopHandsVector();