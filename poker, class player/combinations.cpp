#include "combinations.h"

bool isOnePair(Card & kicker, vector<Card> fullBoard)
{
	sort(fullBoard.begin(), fullBoard.end());

	bool isTrue = false;
	for (int i = fullBoard.size() - 1; i > 0; --i)
	{
		if (fullBoard[i].value == fullBoard[i - 1].value)
		{
			isTrue = true;
			kicker = fullBoard[i];
		}
	}

	return isTrue;
}

bool isTwoPair(Card & kicker1, Card & kicker2, vector<Card> fullBoard)
{
	sort(fullBoard.begin(), fullBoard.end());
	int counter = 0;

	for (int i = fullBoard.size() - 1; i > 0; --i)
	{
		if (counter < 2 && fullBoard[i].value == fullBoard[i - 1].value)
		{
			if (counter == 0)
				kicker1 = fullBoard[i];
			else
				kicker2 = fullBoard[i];

			++counter;
		}
	}

	return counter == 2;
}

bool isThreeOfAKind(Card & kicker, vector<Card> fullBoard)
{
	bool threeOfAKind = true;
	sort(fullBoard.begin(), fullBoard.end());
	for (int i = fullBoard.size() - 1; i >= 2; --i)
	{
		threeOfAKind = true;
		for (int j = 0; j < 3; ++j)
		{
			if (fullBoard[i - j].value != fullBoard[i].value)
			{
				threeOfAKind = false;
				break;
			}
		}

		if (threeOfAKind)
		{
			kicker = fullBoard[i];
			return true;
		}
	}

	return false;
}

bool isStraight(Card & kicker, vector<Card>& fullBoard)
{
	sort(fullBoard.begin(), fullBoard.end());

	bool straight = true;
	for (int i = fullBoard.size() - 1; i >= combinationsSize - 1; --i)
	{
		straight = true;
		for (int j = i; j >= i - combinationsSize + 1; --j)
		{
			if (fullBoard[j - 1].value != fullBoard[j].value - 1)
			{
				straight = false;
				break;
			}
		}

		if (straight == true)
		{
			kicker = fullBoard[i];
			break;
		}
	}

	if (!straight && fullBoard.back().value == Ace)
	{
		fullBoard.push_back(Card(static_cast<Value>(1), Spades));
		sort(fullBoard.begin(), fullBoard.end());

		for (int i = 0; i < combinationsSize - 1; ++i)
		{
			if (fullBoard[i + 1].value != fullBoard[i].value + 1)
			{
				straight = false;
				break;
			}
		}

		kicker = fullBoard[combinationsSize - 1];
		swap(fullBoard[0], fullBoard.back());
		fullBoard.pop_back();
		//sort(fullBoard.begin(), fullBoard.end());
	}

	return straight;
}

bool isFlush(Card & kicker, vector<Card> fullBoard)
{
	bool flush = true;
	for (int i = 0; i < fullBoard.size() - combinationsSize + 1; ++i)
	{
		flush = true;
		for (int j = 0; j < combinationsSize; ++j)
		{
			if (fullBoard[i].color == fullBoard[i + j].color)
			{
				flush = false;
				break;
			}
		}

		if (flush)
		{
			kicker = fullBoard[i];
			break;
		}
	}

	return flush;
}

bool isFullHouse(Card & kicker1, Card & kicker2,  vector<Card> fullBoard)
{
	sort(fullBoard.begin(), fullBoard.end());

	Card threeOfAKindKicker(static_cast<Value>(1), Spades);
	bool threeOfAKind = isThreeOfAKind(threeOfAKindKicker, fullBoard);

	if (!threeOfAKind)
		return false;

	vector<Card> combination;
	auto it = find(fullBoard.begin(), fullBoard.end(), threeOfAKindKicker);
	for (auto boardBegin = fullBoard.begin(); boardBegin < it; ++boardBegin)
		combination.push_back(*boardBegin);
	for (it += 3; it < fullBoard.end(); ++it)
		combination.push_back(*it);

	Card onePairKicker(static_cast<Value>(1), Spades);
	if (isOnePair(onePairKicker, combination))
	{
		kicker1 = threeOfAKindKicker;
		kicker2 = onePairKicker;
		return true;
	}

	return false;
}

bool isFourOfAKind(Card & kicker, vector<Card> fullBoard)
{
	bool fourOfAKind = true;
	sort(fullBoard.begin(), fullBoard.end());
	for (int i = 0; i <= fullBoard.size() - 4; ++i)
	{
		fourOfAKind = true;
		for (int j = 1; j < 4; ++j)
		{
			if (fullBoard[i + j].value != fullBoard[i].value)
			{
				fourOfAKind = false;
				break;
			}
		}

		if (fourOfAKind)
		{
			kicker = fullBoard[i];
			return true;
		}
	}

	return false;
}

bool isStraightFlush(Card & kicker, vector<Card> fullBoard)
{
	Card straightKicker(static_cast<Value>(1), Spades);
	bool straight = isStraight(straightKicker, fullBoard);

	if (!straight)
		return false;

	//sort(fullBoard.begin(), fullBoard.end());
	Card flushKicker(static_cast<Value>(1), Spades);

	vector<Card> combination;
	auto it = find(fullBoard.begin(), fullBoard.end(), straightKicker);
	for (int i = 0; i < combinationsSize; ++i)
		combination.push_back(*(it - i));

	if (isFlush(flushKicker, combination))
	{
		kicker = straightKicker;
		return true;
	}

	return false;
}

bool isRoyalFlush(vector<Card> fullBoard)
{
	sort(fullBoard.begin(), fullBoard.end());
	vector<Card> combination;
	for(int i = fullBoard.size() - combinationsSize; i < fullBoard.size(); ++i)
		combination.push_back(fullBoard[i]);

	Card straightKicker(static_cast<Value>(1), Spades);
	bool str = isStraight(straightKicker, combination);
	if (str && straightKicker.value == Ace)
	{
		Card flushKicker(static_cast<Value>(1), Spades);
		if (isFlush(flushKicker, combination))
			return true;
	}

	return false;
}