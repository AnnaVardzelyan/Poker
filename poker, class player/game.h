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
};