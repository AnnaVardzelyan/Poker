#include "helper_functions.h"
#include "player.h"
#include <ctime>
#include <algorithm>
using namespace std;
void makePokerHand(vector <Card> & deck, Card& card1, Card& card2)
{
	srand(unsigned(time(0)));
	random_shuffle(deck.begin(), deck.end(), [](int i) { return rand() % i; });
	card1 = deck.back();
	deck.pop_back();
	card2 = deck.back();
	deck.pop_back();
}

void makeBoard(vector <Card> & deck, vector<Card> & board)
{
	srand(unsigned(time(0)));
	random_shuffle(deck.begin(), deck.end(), [](int i) { return rand() % i; });
	for (int i = 0; i < 5; ++i)
	{
		board.push_back(deck.back());
		deck.pop_back();
	}
}

vector<Card> generateDeck()
{
	vector<Card> deck;
	for (int i = 2; i <= Ace; ++i)
		for (int j = 0; j <= Spades; ++j)
			deck.push_back(Card(static_cast<Value>(i), static_cast<Color>(j)));
	return move(deck);
}

void PreflopHandsVector(vector < pair < pair<Value, Value>, char >>& preflopHands)
{
	preflopHands.push_back(make_pair(make_pair(Ace, Ace), 'n'));
	preflopHands.push_back(make_pair(make_pair(King, King), 'n'));
	preflopHands.push_back(make_pair(make_pair(Queen, Queen), 'n'));
	preflopHands.push_back(make_pair(make_pair(Ace, King), 's'));
	preflopHands.push_back(make_pair(make_pair(Jack, Jack), 'n'));
	preflopHands.push_back(make_pair(make_pair(Ace, Queen), 's'));
	preflopHands.push_back(make_pair(make_pair(King, Queen), 's'));
	preflopHands.push_back(make_pair(make_pair(Ace, Jack), 's'));
	preflopHands.push_back(make_pair(make_pair(King, Jack), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(10)), 'n'));
	preflopHands.push_back(make_pair(make_pair(Ace, King), 'o'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(10)), 's'));
	preflopHands.push_back(make_pair(make_pair(Queen, Jack), 's'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(10)), 's'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(10)), 's'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(10)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(9)), 'n'));
	preflopHands.push_back(make_pair(make_pair(Ace, Queen), 'o'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(9)), 's'));
	preflopHands.push_back(make_pair(make_pair(King, Queen), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(8)), 'n'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(9)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(9)), 's'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(8)), 's'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(9)), 's'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(9)), 's'));
	preflopHands.push_back(make_pair(make_pair(Ace, Jack), 'o'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(5)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(7), static_cast<Value>(7)), 'n'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(7)), 's'));
	preflopHands.push_back(make_pair(make_pair(King, Jack), 'o'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(4)), 's'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(3)), 's'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(6)), 's'));
	preflopHands.push_back(make_pair(make_pair(Queen, Jack), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(6), static_cast<Value>(6)), 'n'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(8)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(8)), 's'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(2)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(8)), 's'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(8)), 's'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(10)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(8)), 's'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(7)), 's'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(10)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(5), static_cast<Value>(5)), 'n'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(10)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(7)), 's'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(10)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(4), static_cast<Value>(4)), 'n'));
	// Bet or Raise

	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(3), static_cast<Value>(3)), 'n'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(2), static_cast<Value>(2)), 'n'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(6)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(7)), 's'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(5)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(7), static_cast<Value>(6)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(7)), 's'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(4)), 's'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(3)), 's'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(2)), 's'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(7)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(6)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(6), static_cast<Value>(5)), 's'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(7)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(5), static_cast<Value>(4)), 's'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(6)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(7), static_cast<Value>(5)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(6)), 's'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(5)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(6), static_cast<Value>(4)), 's'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(4)), 's'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(3)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(9)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(6)), 's'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(2)), 's'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(9)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(5), static_cast<Value>(3)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(5)), 's'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(6)), 's'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(9)), 'o'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(9)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(5)), 's'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(9)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(4), static_cast<Value>(3)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(7), static_cast<Value>(4)), 's'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(4)), 's'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(3)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(5)), 's'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(2)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(6), static_cast<Value>(3)), 's'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(8)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(5), static_cast<Value>(2)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(5)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(4)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(4)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(3)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(4), static_cast<Value>(2)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(2)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(8)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(8)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(5)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(7)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(7), static_cast<Value>(3)), 's'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(4)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(3), static_cast<Value>(2)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(4)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(3)), 's'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(8)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(3)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(6), static_cast<Value>(2)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(2)), 's'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(8)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(6)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(7)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(8)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(3)), 's'));
	preflopHands.push_back(make_pair(make_pair(Ace, static_cast<Value>(2)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(2)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(7)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(7), static_cast<Value>(2)), 's'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(7), static_cast<Value>(6)), 'o'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(7)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(6), static_cast<Value>(5)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(7)), 'o'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(6)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(6)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(5), static_cast<Value>(4)), 'o'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(5)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(7)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(7), static_cast<Value>(5)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(7)), 'o'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(4)), 'o'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(3)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(6)), 'o'));
	preflopHands.push_back(make_pair(make_pair(King, static_cast<Value>(2)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(6), static_cast<Value>(4)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(6)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(5), static_cast<Value>(3)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(5)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(6)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(5)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(4), static_cast<Value>(3)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(4)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(3)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(7), static_cast<Value>(4)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Queen, static_cast<Value>(2)), 'o'));
	// Call

	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(6)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(6), static_cast<Value>(3)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(5)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(5)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(5), static_cast<Value>(2)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(4)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(3)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(4), static_cast<Value>(2)), 'o'));
	preflopHands.push_back(make_pair(make_pair(Jack, static_cast<Value>(2)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(4)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(5)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(4)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(3), static_cast<Value>(2)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(3)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(7), static_cast<Value>(3)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(10), static_cast<Value>(2)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(6), static_cast<Value>(2)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(4)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(3)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(9), static_cast<Value>(2)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(3)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(8), static_cast<Value>(2)), 'o'));
	preflopHands.push_back(make_pair(make_pair(static_cast<Value>(7), static_cast<Value>(2)), 'o'));
	// Check or Fold
}