#include "cpu_player.h"
#include "combinations.h"
#include "helper_functions.h"
#include "game.h"

int CPUPlayer::Possibility(vector<Card>& fullHand)
{
	Card* kicker1 = new Card(static_cast<Value>(1), Clubs);
	Card* kicker2 = new Card(static_cast<Value>(1), Spades);
	fullHand.push_back(m_card1);
	fullHand.push_back(m_card2);
	int counter = 0;
	vector<Card> deck = generateDeck();

	for (int i = 0; i < fullHand.size(); ++i)
	{
		swap(find(deck.begin(), deck.end(), fullHand[i]), deck.end() - 1);
		deck.pop_back();
	}
	for (int i = 0; i < deck.size(); ++i)
	{
		fullHand.push_back(deck[i]);
		if (isRoyalFlush(fullHand))
			++counter;
		else if (isStraightFlush(*kicker1, fullHand))
			++counter;
		else if (isFourOfAKind(*kicker1, fullHand))
			++counter;
		else if (isFullHouse(*kicker1, *kicker2, fullHand))
			++counter;
		else if (isFlush(*kicker1, fullHand))
			++counter;
		else if (isStraight(*kicker1, fullHand))
			++counter;
		/*else if (isThreeOfAKind(*kicker1, fullHand))
			++counter;
		else if (isTwoPair(*kicker1, *kicker2, fullHand) && ((*kicker1 == m_card1 && *kicker2 == m_card2) || (*kicker2 == m_card1 && *kicker1 == m_card2)))
			++counter;
		else if (isOnePair(*kicker1, fullHand))
			if ((*kicker1).value >= Jack && (*kicker1 == m_card1 || *kicker1 == m_card2))
				++counter;*/

		swap(find(fullHand.begin(), fullHand.end(), deck[i]), fullHand.end() - 1);
		deck.pop_back();
	}

	return ((counter* 100) / deck.size());
}

void CPUPlayer::Preflop(Actions& action, int& amount, const vector<pair<bool, int>>& availableActions, const PlayerPosition& myPosition, int smallBlind)
{
	char c;
	if (m_card1.value == m_card2.value)
		c = 'n';
	else if (m_card1.color == m_card2.color)
		c = 's';
	else if(m_card1.color != m_card2.color)
		c = 'o';

	pair < pair<Value, Value>, char > myHand = make_pair(make_pair(m_card1.value, m_card2.value), c);
	auto it = find_if(preflopHandsVector.begin(), preflopHandsVector.end(), [&](const pair < pair<Value, Value>, char >& elem)
	{
		return (((m_card1.value == (elem.first).first && m_card2.value == (elem.first).second) ||
			(m_card1.value == (elem.first).second && m_card2.value == (elem.first).first)) && c == elem.second);
	});

	int handValue = it - preflopHandsVector.begin();
	if (handValue < 50)
	{
		if (availableActions[AllIn].first)
		{
			if (handValue < 10)
			{
				action = AllIn;
				return;
			}
		}
		if (availableActions[Raise].first)

		{
			if ((availableActions[Raise].second * 4) <= m_money)
			{
				action = Raise;
				amount = availableActions[Raise].second * 2;
			}
			else
				action = Call;
			return;
		}
		if (availableActions[Bet].first)
		{
			action = Bet;
			if (handValue < 10)
			{
				if (availableActions[Bet].second * 4 >= m_money)
					action = AllIn;
				amount = availableActions[Bet].second * 4;
			}
			else if (handValue < 30 && (availableActions[Bet].second * 4) <= m_money)
				 amount = availableActions[Bet].second * 4;
			else // if ((smallBlind * 2) > m_money) => Bet not available
				amount = availableActions[Bet].second * 2;
			return;
		}
		if (availableActions[Call].first)
		{
			// if call amount > m_money => AllIn
			if (handValue < 10)
			{
				action = Call; // amount determined by game
				return;
			}
			else if (handValue < 30)
			{
				if ((availableActions[Call].second * 2) <= m_money)
				{
					action = Call;
					return;
				}
			}
			else if ((availableActions[Call].second * 4) <= m_money)
			{
				action = Call;
				return;
			}
		}
		if (availableActions[Check].first)
		{
			action = Check;
			return;
		}
		action = Fold;
	}
	else if (handValue < 150)
	{
		if (availableActions[Call].first)
			{
				if (handValue < 120)
				{
					if ((availableActions[Call].second * 8) <= m_money)
					{
						action = Call;
						return;
					}
				}
				if (availableActions[Call].second == 2 * smallBlind)
				{
					action = Call;
					return;
				}
			}
		if (availableActions[Check].first == Check)
		{
			action = Check;
			return;
		}
		action = Fold;
	}
	else
	{
		if (availableActions[Check].first)
		{
			action = Check;
			return;
		}
		if (availableActions[Call].first && myPosition == smallBlind && availableActions[Call].second == smallBlind)
		{
			action = Call;
			return;
		}
		action = Fold;
	}
}

void CPUPlayer::Flop(Actions &action, int &amount, int pot, const vector<Card>& board, const vector<pair<bool, int>>& availableActions)
{
	vector<Card> fullHand = board;
	int possibility = Possibility(fullHand);
	if (availableActions[AllIn].first)
	{
		if (possibility >= 99)
		{
			action = AllIn;
			return;
		}
	}
	if (availableActions[Raise].first)
	{
		if (possibility >= 90)
		{
			action = Raise;
			(availableActions[Raise].second * 2 > m_money) ? (amount = m_money) : (amount = availableActions[Raise].second * 2);
			return;
		}
		else if (possibility >= 50)
		{
			action = Call;
			return;
		}
	}
	if (availableActions[Bet].first)
	{
		if (possibility >= 80)
		{
			action = Bet;
			(availableActions[Bet].second * 2 > m_money) ? (amount = m_money) : (availableActions[Bet].second * 2);
		}
		else
			action = Check;
		return;
	}
	if (availableActions[Call].first)
	{
		if (possibility >= 50)
		{
			action = Call;
			return;
		}
	}
	if (availableActions[Check].first)
	{
		action = Check;
		return;
	}
	action = Fold;
}

void CPUPlayer::Turn(Actions &action, int &amount, int pot, const vector<Card>& board, const vector<pair<bool, int>>& availableActions)
{
	vector<Card> fullHand = board;
	int possibility = Possibility(fullHand);
	
	if (availableActions[AllIn].first)
	{
		if (possibility >= 99)
		{
			action = AllIn;
			return;
		}
	}
	if (availableActions[Raise].first)
	{
		if (possibility >= 90)
		{
			action = Raise;
			(availableActions[Raise].second * 2 > m_money) ? (amount = m_money) : (amount = availableActions[Raise].second * 2);
			return;
		}
	}
	if (availableActions[Bet].first)
	{
		if (possibility >= 90)
		{
			action = Bet;
			(availableActions[Bet].second * 2 > m_money) ? (amount = m_money) : (availableActions[Bet].second * 2);
			return;
		}
	}
	if (availableActions[Call].first)
	{
		if (possibility >= 70)
		{
			action = Call;
			return;
		}
	}
	else if (availableActions[Check].first)
	{
		action = Check;
		return;
	}
	action = Fold;
}

void CPUPlayer::River(Actions &action, int &amount, int pot, const vector<Card>& board, const vector<pair<bool, int>>& availableActions)
{
	vector<Card> fullHand = board;
	fullHand.push_back(m_card1);
	fullHand.push_back(m_card2);

	bool combOnBoard = false;
	Card* kicker1 = new Card(static_cast<Value>(1), Clubs);
	Card* kicker2 = new Card(static_cast<Value>(1), Spades);
	if (isRoyalFlush(fullHand))
		combOnBoard = true;
	else if (isStraightFlush(*kicker1, fullHand))
		combOnBoard = true;
	else if (isFourOfAKind(*kicker1, fullHand))
		combOnBoard = true;
	else if (isFullHouse(*kicker1, *kicker2, fullHand))
		combOnBoard = true;
	else if (isFlush(*kicker1, fullHand))
		combOnBoard = true;
	else if (isStraight(*kicker1, fullHand))
		combOnBoard = true;

	if (combOnBoard)
	{
		if (availableActions[Check].first)
			action = Check;
		else
			action = Fold;
		return;
	}

	// at this point the comb can't be only on board
	HandCategories myComb = HighCard;
	if (isRoyalFlush(fullHand))
		myComb = RoyalFlush;
	else if (isStraightFlush(*m_kicker1, fullHand))
		myComb = StraightFlush;
	else if (isFourOfAKind(*m_kicker1, fullHand))
		myComb = FourOfAKind;
	else if (isFullHouse(*m_kicker1, *m_kicker2, fullHand))
		myComb = FullHouse;
	else if (isFlush(*m_kicker1, fullHand))
		myComb = Flush;
	else if (isStraight(*m_kicker1, fullHand))
		myComb = Straight;
	else if (isThreeOfAKind(*m_kicker1, fullHand))
		myComb = ThreeOfAKind;
	else if (isTwoPair(*m_kicker1, *m_kicker2, fullHand))
		myComb = TwoPair;
	else if (isOnePair(*m_kicker1, fullHand))
		myComb = OnePair;

	if (availableActions[AllIn].first)
	{
		if (myComb >= Straight)
		{
			action = AllIn; ///check kicker for Flush and Straight 
			return;
		}
	}
    if (availableActions[Raise].first)
	{
		if (myComb >= ThreeOfAKind)
		{
			action = Raise;
			(availableActions[Raise].second * 2 > m_money) ? (amount = m_money) : (amount = availableActions[Raise].second * 2);
			return;
		}
	}
	if (availableActions[Bet].first)
	{
		if (myComb >= ThreeOfAKind)
		{
			action = Bet;
			(m_money > availableActions[Bet].second * 4) ? (amount = m_money / 2) : (amount = m_money);
			return;
		}
	}
	if (availableActions[Call].first)
	{
		if (myComb > TwoPair)
		{
			action = Call;
			return;
		}
	}
	else if (availableActions[Check].first)
	{
		action = Check;
		return;
	}
	action = Fold;
}