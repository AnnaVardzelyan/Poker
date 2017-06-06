#pragma once
#include "player.h"

bool isOnePair(Card&, vector<Card> fullBoard);
bool isTwoPair(Card&, Card&, vector<Card> fullBoard);
bool isThreeOfAKind(Card&, vector<Card> fullBoard);
bool isStraight(Card&, vector<Card>& fullBoard);
bool isFlush(Card&, vector<Card> fullBoard);
bool isFullHouse(Card&, Card&, vector<Card> fullBoard);
bool isFourOfAKind(Card&, vector<Card> fullBoard);
bool isStraightFlush(Card&, vector<Card> fullBoard);
bool isRoyalFlush(vector<Card> fullBoard);