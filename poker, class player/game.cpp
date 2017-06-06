#include "game.h"
#include <chrono>
#include <ctime>
#include <thread>
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
void Game::PlayGame()
{
	while (players.size() > 1)
	{
		Round r(players);
		players = r.Play(0, 1);

		for (int i = 0; i < players.size(); ++i)
		{
			if (players[i]->m_money < bigBlind)
			{
				players.erase(players.begin() + i);
			}
		}

		cout << "New game will start in 1 second" << endl << endl;
		sleep_until(system_clock::now() + 1s);
	}
}