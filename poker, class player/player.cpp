#include "player.h"
#include <fstream>
#include <string>

HandCategories Player::GetHandCategories() const
{
	return m_handCategories;
}