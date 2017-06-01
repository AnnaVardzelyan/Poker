#include "cpu_player.h"
#include "combinations.h"
#include "helper_functions.h"



void CPUPlayer::Preflop(Actions& action, int& amount, const vector<pair<Actions, int>>& availableActions)
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
				{

				}
			}
		}
	}
	else if (handValue < 100)
	{
		for (int i = 0; i < availableActions.size(); ++i)
		{
			if (availableActions[i].first == AllIn)
			{
				if ((availableActions[i].second * 2) <= m_money)
					action = Call;
				else
					action = Fold;
				break;
			}
		}
	}


}

void CPUPlayer::Flop(Actions &, int &, int, const vector<Card>& board)
{
	//// to fix
	vector<Card> fullHand(5);
	Card* kicker1 = new Card(static_cast<Value>(1), Clubs);
	Card* kicker2 = new Card(static_cast<Value>(1), Spades);
	int cardQuantity = 50 * 49 * 8, counter = 0;
	vector<Card> deck = generateDeck();
	vector<Card> fullHand = board;
	fullHand.push_back(m_card1);
	fullHand.push_back(m_card2);
	for (int i = 0; ; ++i)
	{
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
	}
		////
/*
	double p = (static_cast<double>(counter)) / cardQuantity;
	int odds = p*(pot + amount) + (1 - p)*(-amount);
	if (odds < 0)
		action = Fold;
	else
		action = Call;

	*/
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