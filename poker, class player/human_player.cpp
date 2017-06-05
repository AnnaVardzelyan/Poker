#include "human_player.h"

void HumanPlayer::Preflop(Actions& action,  int& amount, const vector<pair<Actions, int>>& availableActs, const PlayerPosition &myPosition, int Pot)
{
	cout << "Your available actions are: ";
	for (int j = 0; j < availableActs.size(); ++j)
		cout << availableActs[j].first << " ";
	cout << '.' << endl;
	cout << "Please type in your action and press enter." << endl;
	cin >> action;
}

void HumanPlayer::Flop(Actions &, int &, int, const vector<Card>&, const vector<pair<Actions, int>>&)
{
}

void HumanPlayer::Turn(Actions &, int &, int, const vector<Card>&, const vector<pair<Actions, int>>&)
{
}

void HumanPlayer::River(Actions &, int &, int, const vector<Card>&, const vector<pair<Actions, int>>&)
{
}
