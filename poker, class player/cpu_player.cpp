#include "cpu_player.h"
#include "combinations.h"
#include "helper_functions.h"
#include "game.h"


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
	// TO DO
	// check combinations

	vector<Card> fullHand = board;
	fullHand.push_back(m_card1);
	fullHand.push_back(m_card2);
	Card* kicker1 = new Card(static_cast<Value>(1), Clubs);
	Card* kicker2 = new Card(static_cast<Value>(1), Spades);
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
		else if (isTwoPair(*kicker1, *kicker2, fullHand))
			++counter;
		else if (isOnePair(*kicker1, fullHand))
			if ((*kicker1).value >= 6)
				++counter;

		swap(find(fullHand.begin(), fullHand.end(), deck[i]), fullHand.end() - 1);
		deck.pop_back();
	}

	int possibility = (counter * 100) / deck.size();
	//int odds = p*(pot + amount) + (1 - p)*(-amount);
	for (int i = 0; i < availableActions.size(); ++i)
	{
		if (availableActions[i].first == AllIn)
		{
			if (possibility >= 80)
				action = AllIn;
		}

	}
}

void CPUPlayer::Turn(Actions &, int &, int, const vector<Card>& board)
{

}

void CPUPlayer::River(Actions& action, int& amount, int pot, const vector<Card>& board)
{
	vector<Card> fullHand = board;
	fullHand.push_back(m_card1);
	fullHand.push_back(m_card2);

	if (isRoyalFlush(fullHand))
	{

	}
	else if (isStraightFlush(*m_kicker1, fullHand))
	{
	}
	else if (isFourOfAKind(*m_kicker1, fullHand))
	{
		
	}
	else if (isFullHouse(*m_kicker1, *m_kicker2, fullHand))
	{
		
	}
	else if (isFlush(*m_kicker1, fullHand))
	{

	}
	else if (isStraight(*m_kicker1, fullHand))
	{

	}
	else if (isThreeOfAKind(*m_kicker1, fullHand))
	{

	}
	else if (isTwoPair(*m_kicker1, *m_kicker2, fullHand))
	{

	}
	else if (isOnePair(*m_kicker1, fullHand))
	{
		if ((*m_kicker1).value >= 6)
		{

		}
	}
}