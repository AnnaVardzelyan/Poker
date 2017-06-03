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
};