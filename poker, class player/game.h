#pragma once
#include "player.h"
#include "round.h"

class Game
{
public:
	Game()
	{
	}

	void PlayGame();
	vector<Player> players;
	int bigBlind;
	int smallBlind;
	int dealerIndex;
	int pot;
};