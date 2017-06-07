#include "human_player.h"

void HumanPlayer::Preflop(Actions& action,  int& amount, const vector<pair<bool, int>>& availableActs, const PlayerPosition &myPosition, int Pot)
{
	cout << "Your available actions are: ";
	for (int j = 0; j < availableActs.size(); ++j)
	{
		if(availableActs[j].first)
			cout << static_cast<Actions>(j);
		if (availableActs[j].first && j != availableActs.size() - 1)
			cout << " ";
	}
	cout << '.' << endl;
	cout << "Please type in your action and press enter." << endl;
	cin >> action;
}

void HumanPlayer::Flop(Actions & action, int & amount, int pot, const vector<Card>& board, const vector<pair<bool, int>>& availableActs)
{
	cout << "The cards on the board are: " << endl;
	for (int i = 0; i < board.size(); ++i)
		cout << board[i] << endl;
	cout << endl;
	cout << "Your available actions are: ";
	for (int j = 0; j < availableActs.size(); ++j)
	{
		if (availableActs[j].first)
			cout << static_cast<Actions>(j);
		if (availableActs[j].first && j != availableActs.size() - 1)
			cout << " ";
	}
	cout << '.' << endl;
	cout << "Please type in your action and press enter." << endl;
	cin >> action;
}

void HumanPlayer::Turn(Actions & action, int & amount, int pot, const vector<Card>& board, const vector<pair<bool, int>>& availableActs)
{
	cout << "The cards on the board are: " << endl;
	for (int i = 0; i < board.size(); ++i)
		cout << board[i] << endl;
	cout << endl;
	cout << "Your available actions are: ";
	for (int j = 0; j < availableActs.size(); ++j)
	{
		if (availableActs[j].first)
			cout << static_cast<Actions>(j);
		if (availableActs[j].first && j != availableActs.size() - 1)
			cout << " ";
	}
	cout << '.' << endl;
	cout << "Please type in your action and press enter." << endl;
	cin >> action;
}

void HumanPlayer::River(Actions & action, int & amount, int pot, const vector<Card>& board, const vector<pair<bool, int>>& availableActs)
{
	cout << "The cards on the board are: " << endl;
	for (int i = 0; i < board.size(); ++i)
		cout << board[i] << endl;
	cout << endl;
	cout << "Your available actions are: ";
	for (int j = 0; j < availableActs.size(); ++j)
	{
		if (availableActs[j].first)
			cout << static_cast<Actions>(j);
		if (j != availableActs.size() - 1)
			cout << " ";
	}
	cout << '.' << endl;
	cout << "Please type in your action and press enter." << endl;
	cin >> action;
}