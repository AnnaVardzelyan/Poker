#pragma once
#include "player.h"

class CPUPlayer : public Player
{
public:
	CPUPlayer(int money = 1000, PlayerType playerType = CPU)
	{
		m_money = money;
		m_playerType = playerType;
	}
	void Preflop(Actions&, int&, const vector<pair<Actions, int>>&);
	void Flop(Actions&, int&, int, const vector<Card>&);
	void Turn(Actions&, int&, int, const vector<Card>&);
	void River(Actions&, int&, int, const vector<Card>&);
};