#include "card.h"
#include <iostream>
bool operator <(const Card& card1, const Card& card2)
{
	return card1.value < card2.value;
}

bool operator==(const Card & card1, const Card &card2)
{
	return card1.value == card2.value && card1.color == card2.color;
}

ostream & operator<<(ostream & out, const Card & card)
{
	out << card.value << " of ";
	out << card.color << " ";
	return out;
}