#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include "card.h"
#include "enums.h"
#include "helper_functions.h"
using namespace std;
static const int suits = 4;
static const int combinationsSize = 5;


class Game;

class Player
{
public:
	Player()
	{
	}

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