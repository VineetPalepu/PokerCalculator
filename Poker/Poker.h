#pragma once
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>
#include "Card.h"
#include "CardSet.h"

class Poker
{
private:
	static constexpr int NumHands = 9;
	static constexpr std::array<std::array<int, 5>, 21> combos7c5
	{{
		{0,1,2,3,4},
		{0,1,2,3,5},
		{0,1,2,3,6},
		{0,1,2,4,5},
		{0,1,2,4,6},
		{0,1,2,5,6},
		{0,1,3,4,5},
		{0,1,3,4,6},
		{0,1,3,5,6},
		{0,1,4,5,6},
		{0,2,3,4,5},
		{0,2,3,4,6},
		{0,2,3,5,6},
		{0,2,4,5,6},
		{0,3,4,5,6},
		{1,2,3,4,5},
		{1,2,3,4,6},
		{1,2,3,5,6},
		{1,2,4,5,6},
		{1,3,4,5,6},
		{2,3,4,5,6}
	}};

	static constexpr std::array<std::array<int, 2>, 6> combo4c2
	{{
		{0, 1},
		{0, 2},
		{0, 3},
		{1, 2},
		{1, 3},
		{2, 3}
	}};

	static constexpr std::array<std::array<int, 3>, 10> combo5c3
	{{
		{0, 1, 2},
		{0, 1, 3},
		{0, 1, 4},
		{0, 2, 3},
		{0, 2, 4},
		{0, 3, 4},
		{1, 2, 3},
		{1, 2, 4},
		{1, 3, 4},
		{2, 3, 4}
	}};
public:
	enum class Hand
	{
		HighCard,
		OnePair,
		TwoPair,
		ThreeOfAKind,
		Straight,
		Flush,
		FullHouse,
		FourOfAKind,
		StraightFlush
	};

	static constexpr std::array<Hand, NumHands> Hands = {
		Hand::HighCard,
		Hand::OnePair,
		Hand::TwoPair,
		Hand::ThreeOfAKind,
		Hand::Straight,
		Hand::Flush,
		Hand::FullHouse,
		Hand::FourOfAKind,
		Hand::StraightFlush
	};

	static std::tuple<int, int, int, int> texasHoldEmHandProbability(std::vector<CardSet> hand, CardSet table, int trials = 10000);
	static std::tuple<int, int, int, int> omahaHoldEmHandProbability(std::vector<CardSet> hand, CardSet table, int trials = 10000);
	static std::tuple<int, int, int, int, int, int> omahaHoldEmHiLoHandProbability(std::vector<CardSet> hands, CardSet table, int trials = 10000);
	static Hand bestHand(CardSet hand);
	static CardSet bestHandTexasHoldEm(CardSet hand, CardSet table);
	static CardSet bestHandOmahaHoldEm(CardSet hand, CardSet table);
	static CardSet loHandOmahaHoldEm(CardSet hand, CardSet table);
	static int compareHand(CardSet hand1, CardSet hand2);
	static bool comparatorHiHand(CardSet hand1, CardSet hand2);
	static bool comparatorLoHand(CardSet hand1, CardSet hand2);
	static int rankHighCard(CardSet hand1, CardSet hand2);
	static int rankPair(CardSet hand1, CardSet hand2);
	static int rankTriple(CardSet hand1, CardSet hand2);
	static int rankQuad(CardSet hand1, CardSet hand2);
	static int rankStraight(CardSet hand1, CardSet hand2);

	template<std::size_t NUM_COMBOS, std::size_t INDEXES_PER_COMBO>
	static std::vector<CardSet> combinations(CardSet cards, std::array<std::array<int, INDEXES_PER_COMBO>, NUM_COMBOS> comboArr);
};

std::ostream& operator<< (std::ostream& out, const Poker:: Hand& h);