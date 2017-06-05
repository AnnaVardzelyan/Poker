#pragma once
#include "player.h"
#include "round.h"

class Game
{
public:
	Game()
	{
	}
	~Game()
	{
		players.clear();
	}
	void PlayGame();
	vector<Player*> players;
	int bigBlind;
	int smallBlind;
	int dealerIndex;
	int pot;
};