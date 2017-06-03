#pragma once
#include "enums.h"
#include <iostream>
using namespace std;
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
ostream& operator <<(ostream&, const Card&);