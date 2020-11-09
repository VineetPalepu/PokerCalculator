#include "Card.h"

Card::Card(Rank r, Suit s)
    :_rank{ r }, _suit{ s }
{
}

Card::Card(std::string cardStr)
{
    if (cardStr.size() != 2)
        throw std::exception("Card string is not of length 2.");

    Card::Rank rank;
    switch (cardStr[0])
    {
        case 'A':
            rank = Card::Rank::Ace;
            break;
        case '2':
            rank = Card::Rank::Two;
            break;
        case '3':
            rank = Card::Rank::Three;
            break;
        case '4':
            rank = Card::Rank::Four;
            break;
        case '5':
            rank = Card::Rank::Five;
            break;
        case '6':
            rank = Card::Rank::Six;
            break;
        case '7':
            rank = Card::Rank::Seven;
            break;
        case '8':
            rank = Card::Rank::Eight;
            break;
        case '9':
            rank = Card::Rank::Nine;
            break;
        case 'T':
            rank = Card::Rank::Ten;
            break;
        case 'J':
            rank = Card::Rank::Jack;
            break;
        case 'Q':
            rank = Card::Rank::Queen;
            break;
        case 'K':
            rank = Card::Rank::King;
            break;
        default:
            throw std::exception("Invalid character used to specify rank.");
            break;
    }

    Card::Suit suit;
    switch (cardStr[1])
    {
        case 'c':
            suit = Card::Suit::Club;
            break;
        case 'd':
            suit = Card::Suit::Diamond;
            break;
        case 'h':
            suit = Card::Suit::Heart;
            break;
        case 's':
            suit = Card::Suit::Spade;
            break;
        default:
            throw std::exception("Invalid character used to specify suit.");
    }

    _rank = rank;
    _suit = suit;
}

Card::Rank Card::rank() const
{
    return _rank;
}

Card::Suit Card::suit() const
{
    return _suit;
}

bool Card::sortRank(const Card& c1, const Card& c2)
{
    if (c1.rank() == c2.rank())
        return c1.suit() > c2.suit();
    return c1.rank() > c2.rank();
}

bool Card::sortSuit(const Card& c1, const Card& c2)
{
    if (c1.suit() == c2.suit())
        return c1.rank() > c2.rank();
    return c1.suit() > c2.suit();
}

void Card::print()
{
    std::cout << rank() << " of " << suit() << "s";
}

bool operator==(const Card& c1, const Card& c2)
{
    return c1.rank() == c2.rank() && c1.suit() == c2.suit();
}

bool operator!=(const Card& c1, const Card& c2)
{
    return !(c1 == c2);
}


std::ostream& operator<<(std::ostream& out, const Card& c)
{
    switch (c.rank())
    {
        case Card::Rank::Ace:
            out << "A";
            break;
        case Card::Rank::Two:
            out << "2";
            break;
        case Card::Rank::Three:
            out << "3";
            break;
        case Card::Rank::Four:
            out << "4";
            break;
        case Card::Rank::Five:
            out << "5";
            break;
        case Card::Rank::Six:
            out << "6";
            break;
        case Card::Rank::Seven:
            out << "7";
            break;
        case Card::Rank::Eight:
            out << "8";
            break;
        case Card::Rank::Nine:
            out << "9";
            break;
        case Card::Rank::Ten:
            out << "T";
            break;
        case Card::Rank::Jack:
            out << "J";
            break;
        case Card::Rank::Queen:
            out << "Q";
            break;
        case Card::Rank::King:
            out << "K";
            break;
    }

    switch (c.suit())
    {
        case Card::Suit::Club:
            out << "c";
            break;
        case Card::Suit::Diamond:
            out << "d";
            break;
        case Card::Suit::Heart:
            out << "h";
            break;
        case Card::Suit::Spade:
            out << "s";
            break;
    }

    return out;
}

std::ostream& operator<<(std::ostream& out, const Card::Rank& r)
{
    switch (r)
    {
        case Card::Rank::Ace:
            out << "Ace";
            break;
        case Card::Rank::Two:
            out << "Two";
            break;
        case Card::Rank::Three:
            out << "Three";
            break;
        case Card::Rank::Four:
            out << "Four";
            break;
        case Card::Rank::Five:
            out << "Five";
            break;
        case Card::Rank::Six:
            out << "Six";
            break;
        case Card::Rank::Seven:
            out << "Seven";
            break;
        case Card::Rank::Eight:
            out << "Eight";
            break;
        case Card::Rank::Nine:
            out << "Nine";
            break;
        case Card::Rank::Ten:
            out << "Ten";
            break;
        case Card::Rank::Jack:
            out << "Jack";
            break;
        case Card::Rank::Queen:
            out << "Queen";
            break;
        case Card::Rank::King:
            out << "King";
            break;
    }

    return out;
}

std::ostream& operator<<(std::ostream& out, const Card::Suit& s)
{
    switch (s)
    {
        case Card::Suit::Club:
            out << "Club";
            break;
        case Card::Suit::Diamond:
            out << "Diamond";
            break;
        case Card::Suit::Heart:
            out << "Heart";
            break;
        case Card::Suit::Spade:
            out << "Spade";
            break;
    }

    return out;
}
