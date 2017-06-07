#include "round.h"
#include "combinations.h"
#include "card.h"
#include <string>
#include <vector>

//FOR 2 PLAYERS
void Round::PrepareToPlay()
{
	m_deck = generateDeck();
	makeBoard(m_deck, m_board);

	for (int i = 0; i < m_players.size(); ++i)
		makePokerHand(m_deck, (m_players[i])->m_card1, (m_players[i])->m_card2);
}

void Round::CombinationsAndKickers()
{
	for (int i = 0; i < m_players.size(); ++i)
	{
		vector<Card> fullBoard = m_board;
		fullBoard.push_back((m_players[i])->m_card1);
		fullBoard.push_back((m_players[i])->m_card2);

		if (isRoyalFlush(fullBoard))
			(m_players[i])->m_handCategories = RoyalFlush;

		else if (isStraightFlush(*((m_players[i])->m_kicker1), fullBoard))
			(m_players[i])->m_handCategories = StraightFlush;

		else if (isFourOfAKind(*((m_players[i])->m_kicker1), fullBoard))
			(m_players[i])->m_handCategories = FourOfAKind;

		else if (isFullHouse(*((m_players[i])->m_kicker1), *((m_players[i])->m_kicker2), fullBoard))
			(m_players[i])->m_handCategories = FullHouse;

		else if (isFlush(*((m_players[i])->m_kicker1), fullBoard))
			(m_players[i])->m_handCategories = Flush;

		else if (isStraight(*((m_players[i])->m_kicker1), fullBoard))
			(m_players[i])->m_handCategories = Straight;

		else if (isThreeOfAKind(*((m_players[i])->m_kicker1), fullBoard))
			(m_players[i])->m_handCategories = ThreeOfAKind;

		else if (isTwoPair(*((m_players[i])->m_kicker1), *((m_players[i])->m_kicker2), fullBoard))
			(m_players[i])->m_handCategories = TwoPair;

		else if (isOnePair(*((m_players[i])->m_kicker1), fullBoard))
			(m_players[i])->m_handCategories = OnePair;

		else
			(m_players[i])->m_handCategories = HighCard;
	}
}

vector<Player*> Round::Play(int smallBlindPos, int bigBlindPos)
{
	cout << "Round begins." << endl;
	PrepareToPlay();
	
	for (int i = 0; i < m_players.size(); ++i)
	{
		cout << "Player " << i << " cards are ";
		cout << (m_players[i])->m_card1 << ", " << (m_players[i])->m_card2 << '.' << endl;
	}

	cout << "Player " << bigBlindPos << " is the Big Blind" << endl;
	cout << "Player " << smallBlindPos << " is the Small Blind" << endl;
	(m_players[bigBlindPos])->m_money -= 2 * m_smallBlind;
	(m_players[smallBlindPos])->m_money -= m_smallBlind;
	m_pot += 2 * m_smallBlind;
	m_pot += m_smallBlind;
	

	GameStages stage = Preflop;
	int firstBetPos = (bigBlindPos + 1 >= m_players.size()) ? 0 : bigBlindPos + 1;
	vector<pair<bool, int>> availableActs(AllIn + 1);
	for (int i = 0; i < availableActs.size(); ++i)
		availableActs[i].first = false;
	while (true)
	{
		switch (stage)
		{
		case Preflop:
		{
			availableActs[AllIn] = (make_pair(true, 0));
			availableActs[Fold] = (make_pair(true, 0));
			bool hasBeenRaised = false;
			bool called = false;
			bool allIn = false;
			int amount = m_smallBlind;
			while (true)
			{
				for (int i = 0; i < m_players.size(); ++i)
				{
					Actions act;
					PlayerPosition ppos = Nothing;
					(bigBlindPos == i) ? (ppos = BigBlind) : (ppos = SmallBlind);
					if (i == bigBlindPos && !hasBeenRaised)
					{
						availableActs[Check].first = true;
						availableActs[Bet] = (make_pair(false, m_smallBlind * 2));
					}
					if (i == smallBlindPos || hasBeenRaised)
					{
						availableActs[Call] = (make_pair(true, amount));
						availableActs[Raise] = (make_pair(true, amount));
					}
					(m_players[i])->Preflop(act, amount, availableActs, ppos, m_pot);
					switch (act)
					{
					case Fold:
					{
						int winningPlayerPos = 0;
						cout << "Player " << i << " has Folded." << endl;
						(i - 1 < 0) ? (winningPlayerPos = 1) : (winningPlayerPos = 0);
						cout << "The game has ended. Player " << winningPlayerPos << " has won " << m_pot << " $." << endl;
						(m_players[winningPlayerPos])->m_money += m_pot;

						cout << endl << endl;
						return m_players;
					}
					case Check:
						cout << "Player " << i << " has Checked." << endl;
						availableActs[Call].first = false;
						availableActs[Raise].first = false;
						availableActs[Bet].first = false;
						availableActs[Check].first = true;
						availableActs[AllIn].first = false;
						called = true;
						break;
					case Call: // parenthesis to prevent errors with switch
					{

						if (availableActs[Call].second <= (m_players[i])->m_money)
						{
							cout << "Player " << i << " has Called " << availableActs[Call].second << " $." << endl;
							(m_players[i])->m_money -= availableActs[Call].second;
							m_pot += availableActs[Call].second;
						}
						else
						{
							cout << "Player " << i << " has gone All in for" << (m_players[i])->m_money << " $." << endl;
							m_pot += (m_players[i])->m_money;
							(m_players[i])->m_money = 0;
							allIn = true;
						}
						//cout << (m_players[i])->m_money;
						hasBeenRaised = false;
						called = true;
						availableActs[Call].first = false;
						availableActs[Raise].first = false;
						availableActs[Bet].first = false;
						availableActs[Check].first = true;
						availableActs[AllIn].first = true;
					}
					break;
					case Raise:
					{
						if ((m_players[i])->m_playerType == RealPlayer)
						{
							while (true)
							{
								cout << "Please, type in the amount of $ you want to Raise and press Enter. The amount cannot be smaller than "
									<< availableActs[Raise].second << '.' << endl;
								cin >> amount;
								if (amount < availableActs[Raise].second)
								{
									cout << "You've tried to bet less than it is permitted. Try again." << endl;
									continue;
								}
								if (amount + availableActs[Raise].second > (m_players[i])->m_money)
								{
									cout << "You don't have the sufficient funds to make this Raise. Try again.";
									continue;
								}
								break;
							}
						}
						cout << "Player " << i << " Raised the stakes for " << amount << "." << endl;
						availableActs[Raise].second += amount;
						availableActs[Call].second = amount; // - availableActs[Call].second;
						(m_players[i])->m_money -= availableActs[Raise].second;
						m_pot += amount;
						hasBeenRaised = true;
						availableActs[Bet].first = false;
						availableActs[Check].first = false;
						availableActs[Call].first = true;
						availableActs[Raise].first = true;
						availableActs[AllIn].first = true;
					}
					break;
					case AllIn:
						cout << "Player " << i << " has gone All in for" << (m_players[i])->m_money << " $." << endl;
						m_pot += (m_players[i])->m_money;
						availableActs[Call].second = (m_players[i])->m_money;
						amount = (m_players[i])->m_money;
						(m_players[i])->m_money = 0;
						hasBeenRaised = true;
						availableActs[Call].first = true;
						availableActs[Raise].first = false;
						availableActs[Bet].first = false;
						availableActs[Check].first = false;
						allIn = true;
						break;
					default:
						break;
					}
				}
				if (allIn)
					return HasBeenAllIn();

				if (called)
					break;
			}

			cout << endl << endl;
			stage = Flop;
			break;
		}
		case Flop:
		{
			availableActs[AllIn] = (make_pair(true, 0));
			availableActs[Raise] = (make_pair(false, 0));
			availableActs[Fold] = (make_pair(true, 0));
			availableActs[Bet] = (make_pair(true, m_smallBlind * 2));
			availableActs[Call] = (make_pair(false, 0));
			bool hasBeenRaised = false;
			bool bet = false;
			bool called = false;
			bool allIn = false;
			int amount = m_smallBlind;
			vector<Card> board = { m_board[0], m_board[1], m_board[2] };
			while (true)
			{
				for (int i = 0; i < m_players.size(); ++i)
				{
					Actions act;
					PlayerPosition ppos = Nothing;
					(bigBlindPos == i) ? (ppos = BigBlind) : (ppos = SmallBlind);
					if (!hasBeenRaised && !bet)
					{
						availableActs[Check].first = true;
						availableActs[Bet] = (make_pair(true, m_smallBlind * 2));
					}
					if (hasBeenRaised)
					{
						availableActs[Call] = (make_pair(true, amount));
						availableActs[Raise] = (make_pair(true, amount));
					}
					(m_players[i])->Flop(act, amount, m_pot, board, availableActs);
					switch (act)
					{
					case Fold:
					{
						int winningPlayerPos = 0;
						cout << "Player " << i << " has Folded." << endl;
						(i - 1 < 0) ? (winningPlayerPos = 1) : (winningPlayerPos = 0);
						cout << "The game has ended. Player " << winningPlayerPos << " has won " << m_pot << " $." << endl;
						(m_players[winningPlayerPos])->m_money += m_pot;

						cout << endl << endl;
						return m_players;
					}
					case Check:
					{
						cout << "Player " << i << " has Checked." << endl;
						availableActs[Call].first = false;
						availableActs[Raise].first = false;
						availableActs[Bet].first = true;
						availableActs[Check].first = true;
						availableActs[AllIn].first = true;
						called = true;
					}
					break;
					case Call:
					{

						if (availableActs[Call].second <= (m_players[i])->m_money)
						{
							cout << "Player " << i << " has Called " << availableActs[Call].second << " $." << endl;
							(m_players[i])->m_money -= availableActs[Call].second;
							m_pot += availableActs[Call].second;
						}
						else
						{
							cout << "Player " << i << " has gone All in for" << (m_players[i])->m_money << " $." << endl;
							m_pot += (m_players[i])->m_money;
							(m_players[i])->m_money = 0;
							allIn = true;
						}
						//cout << (m_players[i])->m_money;
						availableActs[Call].first = false;
						availableActs[Raise].first = false;
						availableActs[Bet].first = true;
						availableActs[Check].first = true;
						availableActs[AllIn].first = true;
						hasBeenRaised = false;
						called = true;
					}
					break;
					case Bet:
					{
						if ((m_players[i])->m_playerType == RealPlayer)
						{
							while (true)
							{
								cout << "Please, type in the amount of $ you want to Bet and press Enter. The amount cannot be smaller than "
									<< availableActs[Bet].second << '.' << endl;
								cin >> amount;
								if (amount < availableActs[Bet].second)
								{
									cout << "You've tried to bet less than it is permitted. Try again." << endl;
									continue;
								}
								if (amount + availableActs[Bet].second >(m_players[i])->m_money)
								{
									cout << "You don't have the sufficient funds to make this Bet. Try again.";
									continue;
								}
								break;
							}
						}
						cout << "Player " << i << " Bet " << amount << "." << endl;
						availableActs[Raise].second += amount;
						availableActs[Call].second = amount;
						(m_players[i])->m_money -= availableActs[Raise].second;
						m_pot += amount;
						availableActs[Bet].first = false;
						availableActs[Check].first = false;
						availableActs[Call].first = true;
						availableActs[Raise].first = true;
						availableActs[AllIn].first = true;
						bet = true;
						break;
					}
					case Raise:
					{
						if ((m_players[i])->m_playerType == RealPlayer)
						{
							while (true)
							{
								cout << "Please, type in the amount of $ you want to Raise and press Enter. The amount cannot be smaller than "
									<< availableActs[Raise].second << '.' << endl;
								cin >> amount;
								if (amount < availableActs[Raise].second)
								{
									cout << "You've tried to bet less than it is permitted. Try again." << endl;
									continue;
								}
								if (amount + availableActs[Raise].second > (m_players[i])->m_money)
								{
									cout << "You don't have the sufficient funds to make this Raise. Try again.";
									continue;
								}
								break;
							}
						}
						cout << "Player " << i << " Raised the stakes for " << amount << "." << endl;
						availableActs[Raise].second += amount;
						availableActs[Call].second = amount;
						(m_players[i])->m_money -= availableActs[Raise].second;
						m_pot += amount;
						hasBeenRaised = true;
						availableActs[Bet].first = false;
						availableActs[Check].first = false;
						availableActs[Call].first = true;
						availableActs[Raise].first = true;
						availableActs[AllIn].first = true;
					}
					break;
					case AllIn:
					{
						cout << "Player " << i << " has gone All in for" << (m_players[i])->m_money << " $." << endl;
						m_pot += (m_players[i])->m_money;
						availableActs[Call].second = (m_players[i])->m_money;
						amount = (m_players[i])->m_money;
						(m_players[i])->m_money = 0;
						hasBeenRaised = true;
						availableActs[Call].first = true;
						availableActs[Raise].first = false;
						availableActs[Bet].first = false;
						availableActs[Check].first = false;
						allIn = true;
					}
					break;
					}
				}
				if (allIn)
					return HasBeenAllIn();

				if (called)
					break;
			}

			cout << endl << endl;
			stage = Turn;
			break;
		}
		case Turn:
		{
			availableActs[AllIn] = (make_pair(true, 0));
			availableActs[Raise] = (make_pair(true, m_smallBlind * 2));
			availableActs[Fold] = (make_pair(true, 0));
			bool hasBeenRaised = false;
			bool called = false;
			bool allIn = false;
			bool bet = false;
			vector<Card> board = { m_board[0], m_board[1], m_board[2], m_board[3] };
			while (true)
			{
				int amount = m_smallBlind;
				for (int i = 0; i < m_players.size(); ++i)
				{
					Actions act;
					PlayerPosition ppos = Nothing;
					(bigBlindPos == i) ? (ppos = BigBlind) : (ppos = SmallBlind);
					if (!hasBeenRaised)
					{
						availableActs[Check].first = true;
						availableActs[Bet] = (make_pair(true, m_smallBlind * 2));
					}
					if (hasBeenRaised)
					{
						availableActs[Call] = (make_pair(true, amount));
						availableActs[Raise] = (make_pair(true, m_smallBlind * 2));
					}
					(m_players[i])->Turn(act, amount, m_pot, board, availableActs);
					availableActs[Check].first = false;
					availableActs[Call].first = false;
					switch (act)
					{
					case Fold:
					{
						int winningPlayerPos = 0;
						cout << "Player " << i << " has Folded." << endl;
						(i - 1 < 0) ? (winningPlayerPos = 1) : (winningPlayerPos = 0);
						cout << "The game has ended. Player " << winningPlayerPos << " has won " << m_pot << " $." << endl;
						(m_players[winningPlayerPos])->m_money += m_pot;

						cout << endl << endl;
						return m_players;
					}
					case Check:
						cout << "Player " << i << " has Checked." << endl;
						availableActs[Call].first = false;
						availableActs[Raise].first = false;
						availableActs[Bet].first = true;
						availableActs[Check].first = true;
						availableActs[AllIn].first = false;
						called = true;
						break;
					case Call:
					{

						if (availableActs[Call].second <= (m_players[i])->m_money)
						{
							cout << "Player " << i << " has Called " << availableActs[Call].second << " $." << endl;
							(m_players[i])->m_money -= availableActs[Call].second;
							m_pot += availableActs[Call].second;
						}
						else
						{
							cout << "Player " << i << " has gone All in for" << (m_players[i])->m_money << " $." << endl;
							m_pot += (m_players[i])->m_money;
							(m_players[i])->m_money = 0;
							allIn = true;
						}
						//cout << (m_players[i])->m_money;
						availableActs[Call].first = false;
						availableActs[Raise].first = false;
						availableActs[Bet].first = true;
						availableActs[Check].first = true;
						availableActs[AllIn].first = true;
						hasBeenRaised = false;
						called = true;
					}
					break;
					case Bet:
					{
						if ((m_players[i])->m_playerType == RealPlayer)
						{
							while (true)
							{
								cout << "Please, type in the amount of $ you want to Bet and press Enter. The amount cannot be smaller than "
									<< availableActs[Bet].second << '.' << endl;
								cin >> amount;
								if (amount < availableActs[Bet].second)
								{
									cout << "You've tried to bet less than it is permitted. Try again." << endl;
									continue;
								}
								if (amount + availableActs[Bet].second >(m_players[i])->m_money)
								{
									cout << "You don't have the sufficient funds to make this Bet. Try again.";
									continue;
								}
								break;
							}
						}
						cout << "Player " << i << " Bet " << amount << "." << endl;
						availableActs[Raise].second += amount;
						availableActs[Call].second = amount;
						(m_players[i])->m_money -= availableActs[Raise].second;
						m_pot += amount;
						availableActs[Bet].first = false;
						availableActs[Check].first = false;
						availableActs[Call].first = true;
						availableActs[Raise].first = true;
						availableActs[AllIn].first = true;
						bet = true;
						break;
					}
					case Raise:
					{
						if ((m_players[i])->m_playerType == RealPlayer)
							while (true)
							{
								cout << "Please, type in the amount of $ you want to Raise and press Enter. The amount cannot be smaller than "
									<< availableActs[Raise].second << '.' << endl;
								cin >> amount;
								if (amount < availableActs[Raise].second)
								{
									cout << "You've tried to bet less than it is permitted. Try again." << endl;
									continue;
								}
								if (amount + availableActs[Raise].second >(m_players[i])->m_money)
								{
									cout << "You don't have the sufficient funds to make this Raise. Try again.";
									continue;
								}
								break;
							}
						cout << "Player " << i << " Raised the stakes for " << amount << "." << endl;
						availableActs[Raise].second += amount;
						availableActs[Call].second = amount - availableActs[Call].second;
						(m_players[i])->m_money -= availableActs[Raise].second;
						m_pot += amount;
						hasBeenRaised = true;
						availableActs[Bet].first = false;
						availableActs[Check].first = false;
						availableActs[Call].first = true;
						availableActs[Raise].first = true;
						availableActs[AllIn].first = true;
					}
					break;
					case AllIn:
						cout << "Player " << i << " has gone All in for" << (m_players[i])->m_money << " $." << endl;
						m_pot += (m_players[i])->m_money;
						availableActs[Call].second = (m_players[i])->m_money;
						amount = (m_players[i])->m_money;
						(m_players[i])->m_money = 0;
						hasBeenRaised = true;
						availableActs[Call].first = false;
						availableActs[Call].first = true;
						availableActs[Raise].first = false;
						availableActs[Bet].first = false;
						availableActs[Check].first = false;
						allIn = true;
						break;
					default:
						break;
					}
				}
				if (allIn)
					return HasBeenAllIn();

				if (called)
					break;
			}

			cout << endl << endl;
			stage = River;
			break;
		}
		case River:
		{
			availableActs[AllIn] = (make_pair(true, 0));
			availableActs[Raise] = (make_pair(true, m_smallBlind * 2));
			availableActs[Fold] = (make_pair(true, 0));
			bool hasBeenRaised = false;
			bool called = false;
			bool allIn = false;
			bool bet = false;
			vector<Card> board = m_board;
			while (true)
			{
				int amount = m_smallBlind;
				for (int i = 0; i < m_players.size(); ++i)
				{
					Actions act;
					PlayerPosition ppos = Nothing;
					(bigBlindPos == i) ? (ppos = BigBlind) : (ppos = SmallBlind);
					if (!hasBeenRaised)
					{
						availableActs[Check].first = true;
						availableActs[Bet] = (make_pair(true, m_smallBlind * 2));
					}
					if (hasBeenRaised)
					{
						availableActs[Call] = (make_pair(true, amount));
						availableActs[Raise] = (make_pair(true, m_smallBlind * 2));
					}
					(m_players[i])->Turn(act, amount, m_pot, board, availableActs);
					availableActs[Check].first = false;
					availableActs[Call].first = false;
					switch (act)
					{
					case Fold:
					{
						int winningPlayerPos = 0;
						cout << "Player " << i << " has Folded." << endl;
						(i - 1 < 0) ? (winningPlayerPos = 1) : (winningPlayerPos = 0);
						cout << "The game has ended. Player " << winningPlayerPos << " has won " << m_pot << " $." << endl;
						(m_players[winningPlayerPos])->m_money += m_pot;

						cout << endl << endl;
						return m_players;
					}
					case Check:
						cout << "Player " << i << " has Checked." << endl;
						availableActs[Call].first = false;
						availableActs[Raise].first = false;
						availableActs[Bet].first = true;
						availableActs[Check].first = true;
						availableActs[AllIn].first = false;
						called = true;
						break;
					case Call:
					{

						if (availableActs[Call].second <= (m_players[i])->m_money)
						{
							cout << "Player " << i << " has Called " << availableActs[Call].second << " $." << endl;
							(m_players[i])->m_money -= availableActs[Call].second;
							m_pot += availableActs[Call].second;
						}
						else
						{
							cout << "Player " << i << " has gone All in for" << (m_players[i])->m_money << " $." << endl;
							m_pot += (m_players[i])->m_money;
							(m_players[i])->m_money = 0;
							allIn = true;
						}
						//cout << (m_players[i])->m_money;
						availableActs[Call].first = false;
						availableActs[Raise].first = false;
						availableActs[Bet].first = true;
						availableActs[Check].first = true;
						availableActs[AllIn].first = true;
						hasBeenRaised = false;
						called = true;
					}
					break;
					case Bet:
					{
						if ((m_players[i])->m_playerType == RealPlayer)
						{
							while (true)
							{
								cout << "Please, type in the amount of $ you want to Bet and press Enter. The amount cannot be smaller than "
									<< availableActs[Bet].second << '.' << endl;
								cin >> amount;
								if (amount < availableActs[Bet].second)
								{
									cout << "You've tried to bet less than it is permitted. Try again." << endl;
									continue;
								}
								if (amount + availableActs[Bet].second >(m_players[i])->m_money)
								{
									cout << "You don't have the sufficient funds to make this Bet. Try again.";
									continue;
								}
								break;
							}
						}
						cout << "Player " << i << " Bet " << amount << "." << endl;
						availableActs[Raise].second += amount;
						availableActs[Call].second = amount;
						(m_players[i])->m_money -= availableActs[Raise].second;
						m_pot += amount;
						availableActs[Bet].first = false;
						availableActs[Check].first = false;
						availableActs[Call].first = true;
						availableActs[Raise].first = true;
						availableActs[AllIn].first = true;
						bet = true;
					}
					break;
					case Raise:
					{
						if ((m_players[i])->m_playerType == RealPlayer)
							while (true)
							{
								cout << "Please, type in the amount of $ you want to Raise and press Enter. The amount cannot be smaller than "
									<< availableActs[Raise].second << '.' << endl;
								cin >> amount;
								if (amount < availableActs[Raise].second)
								{
									cout << "You've tried to bet less than it is permitted. Try again." << endl;
									continue;
								}
								if (amount + availableActs[Raise].second >(m_players[i])->m_money)
								{
									cout << "You don't have the sufficient funds to make this Raise. Try again.";
									continue;
								}
								break;
							}
						cout << "Player " << i << " Raised the stakes for " << amount << "." << endl;
						availableActs[Raise].second += amount;
						availableActs[Call].second = amount - availableActs[Call].second;
						(m_players[i])->m_money -= availableActs[Raise].second;
						m_pot += amount;
						hasBeenRaised = true;
						availableActs[Bet].first = false;
						availableActs[Check].first = false;
						availableActs[Call].first = true;
						availableActs[Raise].first = true;
						availableActs[AllIn].first = true;
					}
					break;
					case AllIn:
					{
						cout << "Player " << i << " has gone All in for" << (m_players[i])->m_money << " $." << endl;
						m_pot += (m_players[i])->m_money;
						availableActs[Call].second = (m_players[i])->m_money;
						amount = (m_players[i])->m_money;
						(m_players[i])->m_money = 0;
						hasBeenRaised = true;
						availableActs[AllIn].first = false;
						availableActs[Call].first = true;
						availableActs[Raise].first = false;
						availableActs[Bet].first = false;
						availableActs[Check].first = false;
						allIn = true;
					}
						break;
					}
				}
				if (allIn)
					return HasBeenAllIn();

				if (called)
					break;
			}

			cout << endl << endl;
			CompareHands();
			cout << endl << endl;
			return m_players;
		}
		}
	}
}

void Round::CompareHands()
{
	CombinationsAndKickers();

	if (m_players[0]->m_handCategories > m_players[1]->m_handCategories)
	{
		cout << "Player " << 0 << " wins " << m_pot << " with " << m_players[0]->m_handCategories << endl;
		m_players[0]->m_money += m_pot;
		return;
	}
	if(m_players[0]->m_handCategories < m_players[1]->m_handCategories)
	{
		cout << "Player " << 1 << " wins " << m_pot << " with " << m_players[1]->m_handCategories << endl;
		m_players[1]->m_money += m_pot;
		return;
	}
	
	if (*(m_players[0]->m_kicker1) < *(m_players[1]->m_kicker1))
	{
		cout << "Player " << 1 << " wins " << m_pot << " with " << m_players[1]->m_handCategories << " and kicker " << *(m_players[1]->m_kicker1) << endl;
		m_players[1]->m_money += m_pot;
		return;
	}
	if (*(m_players[0]->m_kicker1) == *(m_players[1]->m_kicker1))
	{
		vector<Card> player0 = { m_players[0]->m_card1, m_players[0]->m_card2 };
		vector<Card> player1 = { m_players[1]->m_card1, m_players[1]->m_card2 };
		sort(player0.begin(), player0.end());
		sort(player1.begin(), player1.end());

		if (player0[1] < player1[1])
		{
			cout << "Player " << 1 << " wins " << m_pot << " with " << m_players[1]->m_handCategories 
					<< " and kicker " << player1[1] << '.' << endl;
			m_players[1]->m_money += m_pot;
			return;
		}
		if (player1[1] < player0[1])
		{
			cout << "Player " << 0 << " wins " << m_pot << " with " << m_players[0]->m_handCategories
				<< " and kicker " << player0[1] << '.' << endl;
			m_players[0]->m_money += m_pot;
			return;
		}
		if (player0[0] < player1[0])
		{
			cout << "Player " << 1 << " wins " << m_pot << " with " << m_players[1]->m_handCategories
				<< " and kicker " << player1[0] << '.' << endl;
			m_players[1]->m_money += m_pot;
			return;
		}
		if (player1[0] < player0[0])
		{
			cout << "Player " << 0 << " wins " << m_pot << " with " << m_players[0]->m_handCategories
				<< " and kicker " << player0[0] << '.' << endl;
			m_players[0]->m_money += m_pot;
			return;
		}
		
		cout << "Draw. Both players win " << m_pot / 2 << '.';
		m_players[0]->m_money += m_pot/2;
		m_players[1]->m_money += m_pot/2;
		return;
	}

	cout << "Player " << 0 << " wins " << m_pot << " with " << m_players[0]->m_handCategories << " and kicker " << *(m_players[0]->m_kicker1) << endl;
	m_players[0]->m_money += m_pot;
	return;
}

vector<Player*> Round::HasBeenAllIn()
{
	cout << "The cards on the board are:" << endl;
	for (int i = 0; i < m_board.size(); ++i)
		cout << m_board[i] << endl;

	CompareHands();
	cout << endl << endl;
	return m_players;
}