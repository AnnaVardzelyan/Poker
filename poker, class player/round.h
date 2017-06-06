#pragma once
#include "game.h"
#include "player.h"
#include "helper_functions.h"

class Round 
{
public:
	Round(const vector<Player*>& players)
		:m_players(players)
	{
		m_pot = 0;
		m_smallBlind = 10;
	}
	~Round()
	{
		m_players.clear();
	}
	void PrepareToPlay();
	void CombinationsAndKickers();
	vector<Player*> Play(int, int);
private:
	void CompareHands();
	friend class Game;
	int m_pot;
	int m_smallBlind;
	vector<Card> m_deck;
	vector<Card> m_board;
	vector<Player*> m_players;
};