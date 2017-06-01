#include "round.h"
#include "combinations.h"

void Round::PrepareToPlay()
{
	m_deck = generateDeck();
	makeBoard(m_deck, m_board);

	for (int i = 0; i < m_players.size(); ++i)
		makePokerHand(m_board, m_players[i].m_card1, m_players[i].m_card2);
}

void Round::CombinationsAndKickers()
{
	for (int i = 0; i < m_players.size(); ++i)
	{
		vector<Card> fullBoard = m_board;
		fullBoard.push_back(m_players[i].m_card1);
		fullBoard.push_back(m_players[i].m_card2);

		if (isRoyalFlush(fullBoard))
			m_players[i].m_handCategories = RoyalFlush;

		else if (isStraightFlush(*m_players[i].m_kicker1, fullBoard))
			m_players[i].m_handCategories = StraightFlush;

		else if (isFourOfAKind(*m_players[i].m_kicker1, fullBoard))
			m_players[i].m_handCategories = FourOfAKind;

		else if (isFullHouse(*m_players[i].m_kicker1, *m_players[i].m_kicker2, fullBoard))
			m_players[i].m_handCategories = FullHouse;

		else if (isFlush(*m_players[i].m_kicker1, fullBoard))
			m_players[i].m_handCategories = Flush;

		else if (isStraight(*m_players[i].m_kicker1, fullBoard))
			m_players[i].m_handCategories = Straight;

		else if (isThreeOfAKind(*m_players[i].m_kicker1, fullBoard))
			m_players[i].m_handCategories = ThreeOfAKind;

		else if (isTwoPair(*m_players[i].m_kicker1, *m_players[i].m_kicker2, fullBoard))
			m_players[i].m_handCategories = TwoPair;

		else if (isOnePair(*m_players[i].m_kicker1, fullBoard))
			m_players[i].m_handCategories = OnePair;

		else
			m_players[i].m_handCategories = HighCard;
	}
}

void Round::Play()
{
	PrepareToPlay();
}