#pragma once
#include "player.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "enums.h"
#include "card.h"
using namespace std;

void makePokerHand(vector <Card>&, Card&, Card&);
void makeBoard(vector <Card>&, vector<Card>&);
vector<Card> generateDeck();
void PreflopHandsVector(vector < pair < pair<Value, Value>, char >>&);