#include "game.h"
#include "cpu_player.h"
#include "card.h"
int main()
{
	Game g;
	CPUPlayer pl;
	
	vector<Card>deck = generateDeck();
	vector<Card>board;
	makeBoard(deck, board);



	(g.players).push_back(pl);
}