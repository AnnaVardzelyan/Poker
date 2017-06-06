#include "enums.h"

ostream& operator <<(ostream& out, const Value& val)
{
	switch (val)
	{
	case Jack:
		out << "Jack";
		break;
	case Queen:
		out << "Queen";
		break;
	case King:
		out << "King";
		break;
	case Ace:
		out << "Ace";
		break;
	default:
		out << static_cast<int>(val);
	}

	return out;
}

ostream& operator <<(ostream& out, const Color& col)
{
	switch (col)
	{
	case Hearts:
		out << "Hearts";
		break;
	case Diamonds:
		out << "Diamonds";
		break;
	case Clubs:
		out << "Clubs";
		break;
	case Spades:
		out << "Spades";
	}

	return out;
}

ostream& operator <<(ostream& out, const Actions& act)
{
	switch (act)
	{
	case AllIn:
		out << "AllIn";
		break;
	case Raise:
		out << "Raise";
		break;
	case Bet:
		out << "Bet";
		break;
	case Call:
		out << "Call";
		break;
	case Check:
		out << "Check";
		break;
	case Fold:
		out << "Fold";
		break;
	}
	return out;
}

istream& operator >> (istream& in, Actions& act)
{
	string s;
	in >> s;
	if (s == "AllIn")
		act = AllIn;
	else if (s == "Raise")
		act = Raise;
	else if (s == "Bet")
		act = Bet;
	else if (s == "Call")
		act = Call;
	else if (s == "Check")
		act = Check;
	else if (s == "Fold")
		act = Fold;
	else
		act = static_cast<Actions>(-1);
	return in;
}

ostream & operator<<(ostream & out, HandCategories hCat)
{
	switch (hCat)
	{
	case HighCard:
		out << "High Card";
		break;
	case OnePair:
		out << "One Pair";
		break;
	case TwoPair:
		out << "Two Pair";
		break;
	case ThreeOfAKind:
		out << "Three Of A Kind";
		break;
	case Straight:
		out << "Straight!";
		break;
	case Flush:
		out << "Flush!";
		break;
	case FullHouse:
		out << "Full House!!";
		break;
	case FourOfAKind:
		out << "Four Of A Kind!!";
		break;
	case StraightFlush:
		out << "Straight Flush!!!";
		break;
	case RoyalFlush:
		out << "*** Royal Flush ***";
		break;
	}
	return out;
}