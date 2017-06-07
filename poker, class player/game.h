#pragma once
#include "player.h"
#include "round.h"

class Game
{
public:
	Game()
	{
		bigBlind = 20;
		smallBlind = 10;
	}
	~Game()
	{
		players.clear();
	}
	void PlayGame();
	vector<Player*> players;
	int bigBlind;
	int smallBlind;
	int pot;
};