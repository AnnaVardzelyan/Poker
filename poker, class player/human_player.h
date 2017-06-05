#pragma once
#include "player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(int money = 1000, PlayerType playerType = RealPlayer)
	{
		m_money = money;
		m_playerType = playerType;
	}

	void Preflop(Actions&, int&, const vector<pair<Actions, int>>&, const PlayerPosition&, int);
	void Flop(Actions&, int&, int, const vector<Card>&, const vector<pair<Actions, int>>&);
	void Turn(Actions&, int&, int, const vector<Card>&, const vector<pair<Actions, int>>&);
	void River(Actions&, int&, int, const vector<Card>&, const vector<pair<Actions, int>>&);
};