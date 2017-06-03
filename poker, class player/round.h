#pragma once
#include "game.h"
#include "player.h"
#include "helper_functions.h"

class Round 
{
public:
	Round(const vector<Player>& players)
		:m_players(players)
	{
	}
	
	void PrepareToPlay();
	void CombinationsAndKickers();
	void Play(int);
private:
	friend class Game;
	int m_pot;
	int m_smallBlind;
	vector<Card> m_deck;
	vector<Card> m_board;
	vector<Player> m_players;
};