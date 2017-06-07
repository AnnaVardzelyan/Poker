#include "game.h"
#include "cpu_player.h"
#include "card.h"
#include "human_player.h"
int main()
{
	Game g;
	CPUPlayer *pl1 = new CPUPlayer;
	HumanPlayer *pl2 = new HumanPlayer;

	(g.players).push_back(pl1);
	(g.players).push_back(pl2);
	g.PlayGame();
	(g.players).clear();
	delete pl1;
	delete pl2;
}