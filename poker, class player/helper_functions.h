#pragma once
#include "player.h"

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void makePokerHand(vector <Card>&, Card&, Card&);
void makeBoard(vector <Card>&, vector<Card>&);
vector<Card> generateDeck();
vector < pair < pair<Value, Value>, char >> PreflopHandsVector();