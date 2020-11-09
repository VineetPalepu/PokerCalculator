#include "CardSet.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>

CardSet::CardSet()
    :CardSet("")
{
}

CardSet::CardSet(Type t)
{
    switch (t)
    {
        case Type::Empty:
            cards.reserve(10);
            break;
        case Type::StandardDeck:
            cards.reserve(52);
            for (Card::Suit s : Card::Suits)
            {
                for (Card::Rank r : Card::Ranks)
                {
                    cards.push_back(Card(r, s));
                }
            }
            break;
    }
}

CardSet::CardSet(std::string s)
    :CardSet(Type::Empty)
{
    addFromString(s);
}

void CardSet::add(Card c)
{
    cards.push_back(c);
}

void CardSet::remove(Card c)
{
    cards.erase(std::remove(cards.begin(), cards.end(), c), cards.end());
}

void CardSet::removeAll(CardSet cs)
{
    for (Card c : cs.cards)
    {
        remove(c);
    }
}

int CardSet::count(Card::Rank r) const
{
    int count = 0;
    for (Card c : cards)
    {
        if (c.rank() == r)
            count++;
    }
    return count;
}

int CardSet::count(Card::Suit s) const
{
    int count = 0;
    for (Card c : cards)
    {
        if (c.suit() == s)
            count++;
    }
    return count;
}

std::map<Card::Suit, int> CardSet::suitCount() const
{
    std::map<Card::Suit, int> suitCounts;
    for (Card::Suit s : Card::Suits)
    {
        suitCounts[s] = count(s);
    }

    return suitCounts;
}

int CardSet::maxSuitCount() const
{
    int max = 0;
    for (Card::Suit s : Card::Suits)
    {
        int cnt = count(s);
        if (cnt > max)
            max = cnt;
    }

    return max;
}

std::map<Card::Rank, int> CardSet::rankCount() const
{
    std::map<Card::Rank, int> rankCounts;
    for (Card::Rank r : Card::Ranks)
    {
        rankCounts[r] = count(r);
    }

    return rankCounts;
}

bool CardSet::hasRank(Card::Rank r) const
{
   bool hasR = count(r) > 0;
   return hasR;
}

void CardSet::sortRank()
{
    std::sort(cards.begin(), cards.end(), Card::sortRank);
}

void CardSet::sortSuit()
{
    std::sort(cards.begin(), cards.end(), Card::sortSuit);
}

Card CardSet::deal()
{
    Card c = cards.back();
    cards.pop_back();
    return c;
}

void CardSet::shuffle()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

int CardSet::size() const
{
    return cards.size();
}

void CardSet::print() const
{
    std::cout << (*this) << std::endl;
}

void CardSet::addFromString(std::string s)
{
    std::istringstream iss(s);
    std::vector<std::string> cardStrs { std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
    for (std::string cardStr : cardStrs)
    {
        Card newCard = Card(cardStr);
        cards.push_back(newCard);
    }
}

CardSet CardSet::operator+=(const CardSet& c)
{
    (*this) = (*this) + c;

    return *this;
}

std::ostream& operator<<(std::ostream& out, const CardSet& cs)
{
    out << "[ ";
    for (Card c : cs.cards)
    {
        out << c << " ";
    }
    out << "]";

    return out;
}

CardSet operator+(const CardSet& c1, const CardSet& c2)
{
    CardSet cs = CardSet{ CardSet::Type::Empty };
    for (Card c : c1.cards)
        cs.add(c);
    for (Card c : c2.cards)
        cs.add(c);

    return cs;
}

bool operator==(const CardSet& c1, const CardSet& c2)
{
    bool equal = true;
    if (c1.size() != c2.size())
        return false;

    CardSet cc1 = c1;
    CardSet cc2 = c2;
    
    cc1.sortRank();
    cc2.sortRank();

    for (int i = 0; i < cc1.size(); i++)
    {
        if (cc1.cards[i] != cc2.cards[i])
            return false;
    }
    return true;
}

bool operator!=(const CardSet& c1, const CardSet& c2)
{
    return !(c1 == c2);
}
