#include "player.h"
#include <fstream>
#include <string>
bool operator <(const Card& card1, const Card& card2)
{
	return card1.value < card2.value;
}

bool operator==(const Card & card1, const Card &card2)
{
	return card1.value == card2.value && card1.color == card2.color;
}

HandCategories Player::GetHandCategories() const
{
	return m_handCategories;
}

void Player::Combination()
{
	// ...

	// high card;
}