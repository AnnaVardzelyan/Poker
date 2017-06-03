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
		else if (isThreeOfAKind(*kicker1, fullHand))
			++counter;
		else if (isTwoPair(*kicker1, *kicker2, fullHand) && ((*kicker1 == m_card1 && *kicker2 == m_card2) || (*kicker2 == m_card1 && *kicker1 == m_card2)))
			++counter;
		else if (isOnePair(*kicker1, fullHand))
			if ((*kicker1).value >= Jack && (*kicker1 == m_card1 || *kicker1 == m_card2))
				++counter;

		swap(find(fullHand.begin(), fullHand.end(), deck[i]), fullHand.end() - 1);
		deck.pop_back();
	}

	return ((counter* 100) / deck.size());
}

void CPUPlayer::Preflop(Actions& action, int& amount, const vector<pair<Actions, int>>& availableActions, const PlayerPosition& myPosition, int smallBlind)
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
		for (int i = 0; i < availableActions.size(); ++i)
		{
			if (availableActions[i].first == AllIn)
			{
				// if AllIn available => no other actions
				// Fold not in available action, because always available
				if (handValue < 10)
					action = AllIn;
				else
					action = Fold;
			}
			else if (availableActions[i].first == Raise)
			{
				if ((availableActions[i].second * 4) <= m_money)
				{
					action = Raise;
					amount = availableActions[i].second * 2;
				}
				else
					action = Call;
			}
			else if (availableActions[i].first == Bet)
			{
				action = Bet;
				if (handValue < 10)
					amount = m_money / 4;
				else if (handValue < 30 && (smallBlind * 4) <= m_money)
					amount = smallBlind * 4;
				else // if ((smallBlind * 2) > m_money) => Bet not available
					amount = smallBlind * 2;
			}
			else if (availableActions[i].first == Call)
			{
				// if call amount > m_money => AllIn
				if (handValue < 10)
					action = Call; // amount determined by game
				else if (handValue < 30)
				{
					if ((availableActions[i].second * 2) <= m_money)
						action = Call;
					else
						action = Fold;
				}
				else if ((availableActions[i].second * 4) <= m_money)
					action = Call;
				else
					action = Fold;
			}

			if (action != Fold)
				break;
		}
	}
	else if (handValue < 100)
	{
		for (int i = 0; i < availableActions.size(); ++i)
		{
			if (availableActions[i].first == Call)
			{
				if (handValue < 80)
				{
					if ((availableActions[i].second * 8) <= m_money)
						action = Call;
					else
						action = Fold;
				}
				else if(availableActions[i].second == 2 * smallBlind)
					action = Call;
				else
					action = Fold;

			}
			else if(availableActions[i].first == Check)
				action = Check;

			if (action != Fold)
				break;
		}
	}
	else
	{
		for (int i = 0; i < availableActions.size(); ++i)
		{
			if (availableActions[i].first == Check)
				action = Check;
			else if (availableActions[i].first == Call && myPosition == smallBlind && availableActions[i].second == smallBlind)
				action = Call;
			else
				action = Fold;

			if (action != Fold)
				break;
		}
	}
}

void CPUPlayer::Flop(Actions &action, int &amount, int pot, const vector<Card>& board, const vector<pair<Actions, int>>& availableActions)
{
	vector<Card> fullHand = board;
	int possibility = Possibility(fullHand);
	for (int i = 0; i < availableActions.size(); ++i)
	{
		if (availableActions[i].first == AllIn)
		{
			if (possibility >= 80)
				action = AllIn;
			else
				action = Fold;
		}
		else if (availableActions[i].first == Raise)
		{
			if (possibility >= 80)
			{
				action = Raise;
				(availableActions[i].second * 2 > m_money) ? (amount = m_money) : (amount = availableActions[i].second * 2);
			}
			else if (possibility >= 50)
				action = Call;
			else
				action = Fold;
		}
		else if (availableActions[i].first == Bet)
		{
			if (possibility >= 80)
			{
				action = Bet;
				(SmallBlind * 2 > m_money) ? (amount = m_money) : (SmallBlind * 2);
			}
			else
				action = Check;
		}
		else if (availableActions[i].first == Call)
		{
			if (possibility >= 50)
				action = Call;
			else
				action = Fold;
		}
		else if (availableActions[i].first == Check)
			action = Check;

		if (action != Fold)
			break;
	}
}

void CPUPlayer::Turn(Actions &action, int &amount, int pot, const vector<Card>& board, const vector<pair<Actions, int>>& availableActions)
{
	vector<Card> fullHand = board;
	int possibility = Possibility(fullHand);
	for (int i = 0; i < availableActions.size(); ++i)
	{
		if (availableActions[i].first == AllIn)
		{
			if (possibility >= 90)
				action = AllIn;
			else
				action = Fold;
		}
		else if (availableActions[i].first == Raise)
		{
			if (possibility >= 90)
			{
				action = Raise;
				(availableActions[i].second * 2 > m_money) ? (amount = m_money) : (amount = availableActions[i].second * 2);
			}
			else if (possibility >= 70)
				action = Call;
			else
				action = Fold;
		}
		else if (availableActions[i].first == Bet)
		{
			if (possibility >= 90)
			{
				action = Bet;
				(SmallBlind * 2 > m_money) ? (amount = m_money) : (SmallBlind * 2);
			}
			else
				action = Check;
		}
		else if (availableActions[i].first == Call)
		{
			if (possibility >= 70)
				action = Call;
			else
				action = Fold;
		}
		else if (availableActions[i].first == Check)
			action = Check;

		if (action != Fold)
			break;
	}
}

void CPUPlayer::River(Actions &action, int &amount, int pot, const vector<Card>& board, const vector<pair<Actions, int>>& availableActions)
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
		if (find(availableActions.begin(), availableActions.end(), make_pair(Check, 0)) != availableActions.end())
			action = Check;
		else
			action = Fold;
		return;
	}

	// at this point the comb can't be only on board
	bool betOrAllIn = (find_if(availableActions.begin(), availableActions.end(), [](const pair<Actions, int>& act)
	{
		return (act.first == AllIn || act.first == Raise || act.first == Bet);
	}) != availableActions.end());

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

	for (int i = 0; i < availableActions.size(); ++i)
	{
		if (availableActions[i].first == AllIn)
		{
			if (myComb >= Straight)
				action = AllIn; ///check kicker for Flush and Straight 
			else
				action = Fold;
		}
		else if (availableActions[i].first == Raise)
		{
			if (myComb >= FourOfAKind)
				action = AllIn;
			else if (myComb >= ThreeOfAKind)
			{
				action = Raise;
				(availableActions[i].second * 2 > m_money) ? (amount = m_money) : (amount = availableActions[i].second * 2);
			}
			else
				action = Call;
		}
		else if (availableActions[i].first == Bet)
		{
			if (myComb >= FourOfAKind)
				action = AllIn;
			else if (myComb >= ThreeOfAKind)
			{
				action = Bet;
				(m_money > SmallBlind * 4) ? (amount = m_money / 2) : (amount = m_money);
			}
			else
				action = Check;
		}
		else if (availableActions[i].first == Call)
		{
			if (myComb > Straight)
				action = Call;
			else
				action = Fold;
		}
		else if (availableActions[i].first == Check)
			action = Check;

		if (action != Fold)
			break;
	}
}