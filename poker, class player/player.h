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
	virtual void Preflop(Actions&, int&, const vector<pair<bool, int>>&, const PlayerPosition&, int) = 0 ;
	virtual void Flop(Actions&, int&, int, const vector<Card>&, const vector<pair<bool, int>>&) = 0;
	virtual void Turn(Actions&, int&, int, const vector<Card>&, const vector<pair<bool, int>>&) = 0;
	virtual void River(Actions&, int&, int, const vector<Card>&, const vector<pair<bool, int>>&) = 0;
protected:
	void Combination();
	friend class Round;
	friend class Game;
	int m_money = 1000;
	Card m_card1;
	Card m_card2;
	HandCategories m_handCategories = HighCard;
	Card* m_kicker1 = new Card(static_cast<Value>(1), Clubs);
	Card* m_kicker2 = new Card(static_cast<Value>(1), Spades);
	PlayerType m_playerType;
	bool m_dealer = false;
};