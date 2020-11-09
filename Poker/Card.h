#pragma once

#include <array>
#include <iostream>
#include <string>

class Card
{
public:
    enum class Rank
    {
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,
        Ace
    };

    enum class Suit
    {
        Club,
        Diamond,
        Heart,
        Spade
    };

    static constexpr std::array<Rank, 13> Ranks = {
        Rank::Ace,
        Rank::Two,
        Rank::Three,
        Rank::Four,
        Rank::Five,
        Rank::Six,
        Rank::Seven,
        Rank::Eight,
        Rank::Nine,
        Rank::Ten,
        Rank::Jack,
        Rank::Queen,
        Rank::King
    };

    static constexpr std::array<Suit, 4> Suits = {
        Suit::Club,
        Suit::Diamond,
        Suit::Heart,
        Suit::Spade
    };

private:
    Rank _rank;
    Suit _suit;

public:
    Card(Rank r, Suit s);
    Card(std::string cardStr);

    Rank rank() const;
    Suit suit() const;

    static bool sortRank(const Card& c1, const Card& c2);
    static bool sortSuit(const Card& c1, const Card& c2);

    void print();
};

bool operator== (const Card& c1, const Card& c2);
bool operator!= (const Card& c1, const Card& c2);
std::ostream& operator<< (std::ostream& out, const Card& c);
std::ostream& operator<< (std::ostream& out, const Card::Rank& r);
std::ostream& operator<< (std::ostream& out, const Card::Suit& s);