#include "round.h"
#include "combinations.h"
#include "card.h"
#include <string>
#include <vector>
void Round::PrepareToPlay()
{
	m_deck = generateDeck();
	makeBoard(m_deck, m_board);

	for (int i = 0; i < m_players.size(); ++i)
		makePokerHand(m_deck, m_players[i].m_card1, m_players[i].m_card2);
}

void Round::CombinationsAndKickers()
{
	for (int i = 0; i < m_players.size(); ++i)
	{
		vector<Card> fullBoard = m_board;
		fullBoard.push_back(m_players[i].m_card1);
		fullBoard.push_back(m_players[i].m_card2);

		if (isRoyalFlush(fullBoard))
			m_players[i].m_handCategories = RoyalFlush;

		else if (isStraightFlush(*m_players[i].m_kicker1, fullBoard))
			m_players[i].m_handCategories = StraightFlush;

		else if (isFourOfAKind(*m_players[i].m_kicker1, fullBoard))
			m_players[i].m_handCategories = FourOfAKind;

		else if (isFullHouse(*m_players[i].m_kicker1, *m_players[i].m_kicker2, fullBoard))
			m_players[i].m_handCategories = FullHouse;

		else if (isFlush(*m_players[i].m_kicker1, fullBoard))
			m_players[i].m_handCategories = Flush;

		else if (isStraight(*m_players[i].m_kicker1, fullBoard))
			m_players[i].m_handCategories = Straight;

		else if (isThreeOfAKind(*m_players[i].m_kicker1, fullBoard))
			m_players[i].m_handCategories = ThreeOfAKind;

		else if (isTwoPair(*m_players[i].m_kicker1, *m_players[i].m_kicker2, fullBoard))
			m_players[i].m_handCategories = TwoPair;

		else if (isOnePair(*m_players[i].m_kicker1, fullBoard))
			m_players[i].m_handCategories = OnePair;

		else
			m_players[i].m_handCategories = HighCard;
	}
}

void Round::Play(int smallBlindPos)
{
	cout << "Round begins." << endl;
	PrepareToPlay();
	
	for (int i = 0; i < m_players.size(); ++i)
	{
		cout << "Player " << i << " cards are ";
		cout << m_players[i].m_card1 << ", " << m_players[i].m_card2 << '.' << endl;
	}

	int dealerPos = smallBlindPos, bigBlindPos = - 1;
	if (m_players.size() > 2) 
	{
		if (smallBlindPos - 1 < 0)
		{
			cout << "Player " << m_players.size() - 1 << " is the Dealer." << endl;
			dealerPos = m_players.size() - 1;
		}
		else
		{
			cout << "Player " << smallBlindPos - 1 << " is the Dealer." << endl;
			dealerPos = smallBlindPos - 1;
		}
	}

	cout << "Player " << smallBlindPos << " is the Small Blind." << endl;
	m_players[smallBlindPos].m_money -= m_smallBlind; // game checks if m_money < 2 * m_smallBlind
	m_pot += m_smallBlind;

	if (smallBlindPos + 1 == m_players.size())
	{
		cout << "Player " << 0 << " is the Big Blind." << endl;
		m_players[0].m_money -= m_smallBlind * 2;
		bigBlindPos = 0;
	}
	else
	{
		cout << "Player " << smallBlindPos + 1 << " is the Big Blind." << endl;
		m_players[smallBlindPos + 1].m_money -= m_smallBlind * 2;
		bigBlindPos = smallBlindPos + 1;
	}

	m_pot += 2 * m_smallBlind;
	
	vector<int> foldedPlayersIndexes;
	GameStages stage = Preflop;
	int firstBetPos = (bigBlindPos + 1 >= m_players.size()) ? 0 : bigBlindPos + 1;
	vector<pair <Actions, int>> availableActs;

	switch (stage)
	{
	case Preflop:
		availableActs.push_back(make_pair(AllIn, 0));
		availableActs.push_back(make_pair(Raise, m_smallBlind*2));
		availableActs.push_back(make_pair(Call, m_smallBlind*2));
		availableActs.push_back(make_pair(Fold, 0));
		bool hasBeenRaised = false;
		while (true)
		{
			for (int i = firstBetPos; i < m_players.size(); ++i)
			{
				if (find(foldedPlayersIndexes.begin(), foldedPlayersIndexes.end(), i) != foldedPlayersIndexes.end())
					continue;

				if (m_players[i].m_playerType == RealPlayer)
				{
					cout << "Player " << i << "\nYour available actions are: ";
					for (int j = 0; j < availableActs.size(); ++j)
						cout << availableActs[i].first << " ";
					if (i == bigBlindPos && hasBeenRaised)
						cout << Check;
					cout << '.' << endl;
					cout << "Please type in your action and press enter." << endl;
					Actions act;
					cin >> act;
					switch (act)
					{
					case Fold:
						cout << "Player " << i << " has Folded." << endl;
						foldedPlayersIndexes.push_back(i);
						break;
					case Check:
						cout << "Player " << i << " has Checked." << endl;
						break;
					case Call: // parenthesis to prevent errors with switch
					{
						auto it = find_if(availableActs.begin(), availableActs.end(), [](const pair<Actions, int>& elem)
						{
							return elem.first == Call;
						});
						if (it->second <= m_players[i].m_money)
						{
							cout << "Player " << i << " has Called " << it->second << " $." << endl;
							m_players[i].m_money -= it->second;
							m_pot += it->second;
						}
						else
						{
							// if 2 players are playing and one goes all in, then the 2nd one can't raise or bet
							// if one of the players goes all in and others continue to raise, they have a different pot
							cout << "Player " << i << " has gone All in for" << m_players[i].m_money << " $." << endl;
							m_pot += m_players[i].m_money;
							m_players[i].m_money = 0;
						}
					}
					break;
					case Raise:
					{
						auto it1 = find_if(availableActs.begin(), availableActs.end(), [](const pair<Actions, int>& elem)
						{
							return elem.first == Raise;
						});
						auto it2 = find_if(availableActs.begin(), availableActs.end(), [](const pair<Actions, int>& elem)
						{
							return elem.first == Call;
						});
						int amnt;
						while (true)
						{
							cout << "Please, type in the amount of $ you want to Raise and press Enter. The amount cannot be smaller than "
								 << it1->second << '.' << endl;
							cin >> amnt;
							if(amnt < it1->second)
							{
								cout << "You've tried to bet less than it is permitted. Try again." << endl;
								continue;
							}
							if(amnt + it1->second > m_players[i].m_money)
							{
								cout << "You don't have the sufficient funds to make this Raise. Try again.";
								continue;
							}
							break;
						}
						cout << "Player " << i << "Raised the stakes for " << amnt << "." << endl;
						it1->second += amnt;
						it2->second = it1->second
						m_players[i].m_money -= it1->second;
						m_pot += amnt;
						hasBeenRaised = true;
					}
					break;
					case AllIn:
						cout << "Player " << i << " has gone All in for" << m_players[i].m_money << " $." << endl;
						m_pot += m_players[i].m_money;
						m_players[i].m_money = 0;
						break;
					default:
						break;
					}

				}

			}
			for (int i = 0; i <= smallBlindPos; ++i)
			{
				if (find(foldedPlayersIndexes.begin(), foldedPlayersIndexes.end(), i) != foldedPlayersIndexes.end())
					continue;

				if (m_players[i].m_playerType == RealPlayer)
				{
					cout << "Player " << i << "\nYour available actions are: ";
					for (int j = 0; j < availableActs.size(); ++j)
						cout << availableActs[i].first << " ";
					if (i == bigBlindPos && hasBeenRaised)
						cout << Check;
					cout << '.' << endl;
					cout << "Please type in your action and press enter." << endl;
					Actions act;
					cin >> act;
					switch (act)
					{
					case Fold:
						cout << "Player " << i << " has Folded." << endl;
						foldedPlayersIndexes.push_back(i);
						break;
					case Check:
						cout << "Player " << i << " has Checked." << endl;
						break;
					case Call: // parenthesis to prevent errors with switch
					{
						auto it = find_if(availableActs.begin(), availableActs.end(), [](const pair<Actions, int>& elem)
						{
							return elem.first == Call;
						});
						if (it->second <= m_players[i].m_money)
						{
							cout << "Player " << i << " has Called " << it->second << " $." << endl;
							m_players[i].m_money -= it->second;
							m_pot += it->second;
						}
						else
						{
							// if 2 players are playing and one goes all in, then the 2nd one can't raise or bet
							// if one of the players goes all in and others continue to raise, they have a different pot
							cout << "Player " << i << " has gone All in for" << m_players[i].m_money << " $." << endl;
							m_pot += m_players[i].m_money;
							m_players[i].m_money = 0;
						}
					}
					break;
					case Raise:
					{
						auto it1 = find_if(availableActs.begin(), availableActs.end(), [](const pair<Actions, int>& elem)
						{
							return elem.first == Raise;
						});
						auto it2 = find_if(availableActs.begin(), availableActs.end(), [](const pair<Actions, int>& elem)
						{
							return elem.first == Call;
						});
						int amnt;
						while (true)
						{
							cout << "Please, type in the amount of $ you want to Raise and press Enter. The amount cannot be smaller than "
								 << it1->second << '.' << endl;
							cin >> amnt;
							if(amnt < it1->second)
							{
								cout << "You've tried to bet less than it is permitted. Try again." << endl;
								continue;
							}
							if(amnt + it1->second > m_players[i].m_money)
							{
								cout << "You don't have the sufficient funds to make this Raise. Try again.";
								continue;
							}
							break;
						}
						cout << "Player " << i << "Raised the stakes for " << amnt << "." << endl;
						it1->second += amnt;
						it2->second = it1->second
						m_players[i].m_money -= it1->second;
						m_pot += amnt;
						hasBeenRaised = true;
					}
					break;
					case AllIn:
						cout << "Player " << i << " has gone All in for" << m_players[i].m_money << " $." << endl;
						m_pot += m_players[i].m_money;
						m_players[i].m_money = 0;
						break;
					default:
						break;
					}

				}
			}
			if(!hasBeenRaised)
				break;
			hasBeenRaised = false;
			if(foldedPlayersIndexes.size() == m_players.size() - 1)
			{
				for(int i = 0; i < m_players.size(); ++i)
				{
					if(find(foldedPlayersIndexes.begin(), foldedPlayersIndexes.end(), i) != foldedPlayersIndexes.end())
					{
						cout << "The Round has ended. Player " << i << " has won the pot in the amount of " << m_pot << " $." << endl;
						m_players[i].m_money += m_pot;
						return;
					}
				}
			}
		}

		break;

	case Flop:
			while (true)
			{
				
			}
		break;


	case Turn:
		break;


	case River:
		break;
	}
}
