#pragma once

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
	Dealer,
	SmallBlind,
	BigBlind
};
