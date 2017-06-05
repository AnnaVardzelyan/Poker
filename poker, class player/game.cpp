#include "game.h"

void Game::PlayGame()
{
	// Qt menu player selection
	
	Round r(players);
	r.Play(0, 1);

	/*if (players.size() > 1 && players.size() <= 5)
		r.Play();*/
	
}