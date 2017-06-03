#pragma once
#include "player.h"
#include "helper_functions.h"
#include <vector>
class CPUPlayer : public Player
{
public:
	CPUPlayer(int money = 1000, PlayerType playerType = CPU)
	{
		m_money = money;
		m_playerType = playerType;
		PreflopHandsVector(preflopHandsVector);
	}
	void Preflop(Actions&, int&, const vector<pair<Actions, int>>&, const PlayerPosition&, int);
	void Flop(Actions&, int&, int, const vector<Card>&, const vector<pair<Actions, int>>&);
	void Turn(Actions&, int&, int, const vector<Card>&, const vector<pair<Actions, int>>&);
	void River(Actions&, int&, int, const vector<Card>&, const vector<pair<Actions, int>>&);

private:
	int Possibility(vector<Card>&);
	vector < pair < pair<Value, Value>, char >> preflopHandsVector;
};