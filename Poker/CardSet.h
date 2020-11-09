#pragma once

#include <vector>
#include <map>
#include <string>

#include "Card.h"

class CardSet
{
	std::vector<Card> cards;

public:
	enum class Type {
		Empty,
		StandardDeck
	};

	CardSet();
	CardSet(Type t);
	CardSet(std::string s);

	void add(Card c);
	void remove(Card c);

	void removeAll(CardSet cs);

	int count(Card::Rank r) const;
	int count(Card::Suit s) const;

	std::map<Card::Suit, int> suitCount() const;
	int maxSuitCount() const;

	std::map<Card::Rank, int> rankCount() const;

	bool hasRank(Card::Rank r) const;

	void sortRank();
	void sortSuit();

	Card deal();
	void shuffle();
	int size() const;
	void print() const;
	friend std::ostream& operator<< (std::ostream& out, const CardSet& c);

	void addFromString(std::string s);

	friend CardSet operator+ (const CardSet& c1, const CardSet& c2);
	CardSet operator+= (const CardSet& c);
	friend bool operator== (const CardSet& c1, const CardSet& c2);
	friend bool operator!= (const CardSet& c1, const CardSet& c2);

	friend class Poker;
};


