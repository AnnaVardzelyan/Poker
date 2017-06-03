#pragma once
#include "enums.h"
class Card
{
public:
	Card(Value value = static_cast<Value>(1), Color color = Hearts)
		:value(value)
		, color(color)
	{
	}

	Value value;
	Color color;
};

bool operator <(const Card&, const Card&);
bool operator ==(const Card&, const Card&);