#pragma once
#include <iostream>
#include <string>
using namespace std;

enum PlayerType
{
	RealPlayer,
	CPU
};
enum Color
{
	Hearts,
	Diamonds,
	Clubs,
	Spades,
};
enum Value
{
	Jack = 11,
	Queen,
	King,
	Ace
};
enum HandCategories
{
	HighCard,
	OnePair,
	TwoPair,
	ThreeOfAKind,
	Straight,
	Flush,
	FullHouse,
	FourOfAKind,
	StraightFlush,
	RoyalFlush
};
enum Actions
{
	Fold,
	Check,
	Call,
	Bet,
	Raise,
	AllIn
};
enum PlayerPosition
{
	Nothing,
	Dealer,
	SmallBlind,
	BigBlind
};
enum GameStages
{
	Preflop,
	Flop,
	Turn,
	River
};

ostream& operator <<(ostream&, const Value&);
ostream& operator <<(ostream&, const Color&);
ostream& operator <<(ostream&, const Actions&);
istream& operator >>(istream&, Actions&);
ostream& operator <<(ostream&, HandCategories);