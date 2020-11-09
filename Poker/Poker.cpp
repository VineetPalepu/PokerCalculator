#include "Poker.h"



std::tuple<int, int, int, int> Poker::texasHoldEmHandProbability(std::vector<CardSet> hands, CardSet table, int trials)
{
    const int handSize = 2;
    const int tableSize = 5;

    CardSet deck{ CardSet::Type::StandardDeck };
    for (CardSet hand : hands)
    {
        deck.removeAll(hand);
    }
    deck.removeAll(table);

    int wins = 0, losses = 0, ties = 0;
    for (int i = 0; i < trials; i++)
    {
        CardSet d = deck;
        d.shuffle();

        std::vector<CardSet> fullDealtHands = hands;
        for (CardSet& playerHand : fullDealtHands)
        {
            int initialSize = playerHand.size();
            for (int j = 0; j < handSize - initialSize; j++)
            {
                playerHand.add(d.deal());
            }
        }
        CardSet t = table;
        int initialSize = t.size();
        for (int j = 0; j < tableSize - initialSize; j++)
        {
            t.add(d.deal());
        }

        std::vector<CardSet> bestHands;
        for (int j = 0; j < fullDealtHands.size(); j++)
        {
            bestHands.push_back(Poker::bestHandTexasHoldEm(fullDealtHands[j], t));
        }
        
        CardSet p1Hand = bestHands[0];
        
        std::sort(bestHands.begin(), bestHands.end(), comparatorHiHand);
        
        if (compareHand(p1Hand, bestHands[bestHands.size() - 1]) == 0)
        {
            if (compareHand(p1Hand, bestHands[bestHands.size() - 2]) == 0)
                ties++;
            else
                wins++;
        }
        else
        {
            losses++;
        }
            
    }

    return {wins, ties, losses, trials};
}

std::tuple<int, int, int, int> Poker::omahaHoldEmHandProbability(std::vector<CardSet> hands, CardSet table, int trials)
{
    const int handSize = 4;
    const int tableSize = 5;

    CardSet deck{ CardSet::Type::StandardDeck };
    for (CardSet hand : hands)
    {
        deck.removeAll(hand);
    }
    deck.removeAll(table);

    int wins = 0, losses = 0, ties = 0;
    for (int i = 0; i < trials; i++)
    {
        CardSet d = deck;
        d.shuffle();

        std::vector<CardSet> fullDealtHands = hands;
        for (CardSet& playerHand : fullDealtHands)
        {
            int initialSize = playerHand.size();
            for (int j = 0; j < handSize - initialSize; j++)
            {
                playerHand.add(d.deal());
            }
        }
        CardSet t = table;
        int initialSize = t.size();
        for (int j = 0; j < tableSize - initialSize; j++)
        {
            t.add(d.deal());
        }

        std::vector<CardSet> bestHands;
        for (int j = 0; j < fullDealtHands.size(); j++)
        {
            bestHands.push_back(Poker::bestHandOmahaHoldEm(fullDealtHands[j], t));
        }

        CardSet p1Hand = bestHands[0];

        std::sort(bestHands.begin(), bestHands.end(), comparatorHiHand);

        if (compareHand(p1Hand, bestHands[bestHands.size() - 1]) == 0)
        {
            if (compareHand(p1Hand, bestHands[bestHands.size() - 2]) == 0)
                ties++;
            else
                wins++;
        }
        else
        {
            losses++;
        }

    }

    return { wins, ties, losses, trials };
}

std::tuple<int, int, int, int, int, int> Poker::omahaHoldEmHiLoHandProbability(std::vector<CardSet> hands, CardSet table, int trials)
{
    const int handSize = 4;
    const int tableSize = 5;

    CardSet deck{ CardSet::Type::StandardDeck };
    for (CardSet hand : hands)
    {
        deck.removeAll(hand);
    }
    deck.removeAll(table);

    int scoop = 0, winsHi = 0, winsLo = 0, tiesHi = 0, tiesLo = 0, losses = 0;
    double equitySum = 0;
    for (int i = 0; i < trials; i++)
    {
        CardSet d = deck;
        d.shuffle();

        std::vector<CardSet> fullDealtHands = hands;
        for (CardSet& playerHand : fullDealtHands)
        {
            int initialSize = playerHand.size();
            for (int j = 0; j < handSize - initialSize; j++)
            {
                playerHand.add(d.deal());
            }
        }
        CardSet t = table;
        int initialSize = t.size();
        for (int j = 0; j < tableSize - initialSize; j++)
        {
            t.add(d.deal());
        }

        std::vector<CardSet> bestHands;
        for (int j = 0; j < fullDealtHands.size(); j++)
        {
            bestHands.push_back(Poker::bestHandOmahaHoldEm(fullDealtHands[j], t));
        }

        std::vector<CardSet> loHands;
        for (int j = 0; j < fullDealtHands.size(); j++)
        {
            loHands.push_back(Poker::loHandOmahaHoldEm(fullDealtHands[j], t));
        }

        CardSet p1HiHand = bestHands[0];
        std::sort(bestHands.begin(), bestHands.end(), comparatorHiHand);
        
        double equity = 0;
        if (compareHand(p1HiHand, bestHands[bestHands.size() - 1]) == 0)
        {
            if (compareHand(p1HiHand, bestHands[bestHands.size() - 2]) == 0)
            {
                equity += .25;
                tiesHi++;
            }
            else
            {
                equity += .5;
                winsHi++;
            }
        }
        int numLoHands = 0;
        for (auto hand : loHands)
        {
            if (hand.size() != 0)
                numLoHands++;
        }
        if (numLoHands > 0)
        {
            CardSet p1LoHand = loHands[0];
            std::sort(loHands.begin(), loHands.end(), comparatorLoHand);


            if (p1LoHand.rankCount() == loHands[loHands.size() - 1].rankCount()) // p1 has winning / tie lo hand
            {
                if (p1LoHand.rankCount() == loHands[loHands.size() - 2].rankCount())
                {
                    equity += .25;
                    tiesLo++;
                }
                else
                {
                    equity += .5;
                    winsLo++;
                }
            }

        }
        else
        {
            equity *= 2;
            
        }

        equitySum += equity;
    }
    
    std::cout << std::endl;
    std::cout << "Wins Hi: " << winsHi * 100. / trials << "%" << std::endl;
    std::cout << "Ties Hi: " << tiesHi * 100. / trials << "%" << std::endl;
    std::cout << "Wins Lo: " << winsLo * 100. / trials << "%" << std::endl;
    std::cout << "Ties Lo: " << tiesLo * 100. / trials << "%" << std::endl;
    std::cout << "Equity: " << equitySum * 100 / trials << "%" << std::endl;
    std::cout << std::endl;

    return { winsHi, winsLo, tiesHi, tiesLo, losses, trials };
}

Poker::Hand Poker::bestHand(CardSet hand)
{
    if (hand.size() != 5)
        throw std::exception("Wrong number of cards in hand.");

    bool flush = false;
    bool straight = false;
    bool quad = false;
    bool triple = false;
    int pairs = 0;

    if (hand.maxSuitCount() == 5) // Flush
        flush = true;

    for (Card::Rank r : Card::Ranks)
    {
        int rankCount = hand.count(r);
        if (rankCount == 4)
            quad = true;
        if (rankCount == 3)
            triple = true;
        if (rankCount == 2)
            pairs++;
    }

    hand.sortRank();
    Card::Rank highRankCard = hand.cards[0].rank();
    bool consecutive = true;
    for (int i = 0; i < 5; i++)
    {
        if (!hand.hasRank((Card::Rank)((int)highRankCard - i)))
        {
            consecutive = false;
            break;
        }
    }
    if (!consecutive && highRankCard == Card::Rank::Ace)
    {
        consecutive = true;
        for (int i = 0; i < 4; i++)
        {
            if (!hand.hasRank((Card::Rank)((int)Card::Rank::Five - i)))
            {
                consecutive = false;
                break;
            }
        }
    }
    straight = consecutive;

    if (straight && flush)
        return Hand::StraightFlush;
    else if (quad)
        return Hand::FourOfAKind;
    else if (triple && pairs == 1)
        return Hand::FullHouse;
    else if (flush)
        return Hand::Flush;
    else if (straight)
        return Hand::Straight;
    else if (triple)
        return Hand::ThreeOfAKind;
    else if (pairs == 2)
        return Hand::TwoPair;
    else if (pairs == 1)
        return Hand::OnePair;
    else
        return Hand::HighCard;
}

CardSet Poker::bestHandTexasHoldEm(CardSet hand, CardSet table)
{
    if (hand.size() != 2 && table.size() != 5)
        throw std::invalid_argument("Wrong size hand and/or table");

    CardSet all7Cards = hand + table;

    std::vector<CardSet> possibleHands = combinations(all7Cards, Poker::combos7c5);
    return *std::max_element(possibleHands.begin(), possibleHands.end(), comparatorHiHand);
}

CardSet Poker::bestHandOmahaHoldEm(CardSet hand, CardSet table)
{
    if (hand.size() != 4 && table.size() != 5)
        throw std::invalid_argument("Wrong size hand and/or table");
    
    std::vector<CardSet> handCombos = combinations(hand, combo4c2);
    std::vector <CardSet> tableCombos = combinations(table, combo5c3);

    std::vector<CardSet> possibleHands;

    for (CardSet hand2Cards : handCombos)
    {
        for (CardSet table3Cards : tableCombos)
        {
            possibleHands.push_back(hand2Cards + table3Cards);
        }
    }

    return *std::max_element(possibleHands.begin(), possibleHands.end(), comparatorHiHand);
}

CardSet Poker::loHandOmahaHoldEm(CardSet playerHand, CardSet table)
{
    if (playerHand.size() != 4 && table.size() != 5)
        throw std::invalid_argument("Wrong size hand and/or table");

    std::vector<CardSet> handCombos = combinations(playerHand, combo4c2);
    std::vector <CardSet> tableCombos = combinations(table, combo5c3);

    std::vector<CardSet> possibleHands;

    for (CardSet hand2Cards : handCombos)
    {
        for (CardSet table3Cards : tableCombos)
        {
            possibleHands.push_back(hand2Cards + table3Cards);
        }
    }

    std::vector<CardSet> loHands;
    for (CardSet hand : possibleHands)
    {
        Hand handType = bestHand(hand);
        if (handType == Hand::HighCard || handType == Hand::Straight
            || handType == Hand::Flush || handType == Hand::StraightFlush)
        {
            // We now know that the hand is unpaired
            // Now we need to check if the only ranks are 8 or lower
            std::array<Card::Rank, 5> hiRanks =
            {
                Card::Rank::Nine,
                Card::Rank::Ten,
                Card::Rank::Jack,
                Card::Rank::Queen,
                Card::Rank::King
            };
            bool hadHiRank = false;
            auto rankCount = hand.rankCount();
            for (auto rank : hiRanks)
            {
                if (rankCount[rank] > 0)
                    hadHiRank = true;
            }

            if (!hadHiRank)
                loHands.push_back(hand);
        }
    }

    if (loHands.size() == 0)
        return CardSet();

    return *std::max_element(loHands.begin(), loHands.end(), comparatorLoHand);
}

int Poker::compareHand(CardSet hand1, CardSet hand2)
{
    auto h1 = Poker::bestHand(hand1);
    auto h2 = Poker::bestHand(hand2);
    if (h1 > h2)
        return 1;
    else if (h1 < h2)
        return -1;
    else
    {
        hand1.sortRank();
        hand2.sortRank();

        if (h1 == Hand::HighCard)
        {
            return rankHighCard(hand1, hand2);
        }
        else if (h1 == Hand::OnePair)
        {
            return rankPair(hand1, hand2);
        }
        else if (h1 == Hand::TwoPair)
        {
            return rankPair(hand1, hand2);
        }
        else if (h1 == Hand::ThreeOfAKind)
        {
            return rankTriple(hand1, hand2);
        }
        else if (h1 == Hand::Straight)
        {
            return rankStraight(hand1, hand2);
        }
        else if (h1 == Hand::Flush)
        {
            return rankHighCard(hand1, hand2);
        }
        else if (h1 == Hand::FullHouse)
        {
            int comp = rankTriple(hand1, hand2);
            if (comp == 0)
            {
                return rankPair(hand1, hand2);
            }
            return comp;
        }
        else if (h1 == Hand::FourOfAKind)
        {
            return rankQuad(hand1, hand2);
        }
        else if (h1 == Hand::StraightFlush)
        {
            return rankStraight(hand1, hand2);
        }
        else
        {
            throw std::exception("Fucked");
        }
    }
}

bool Poker::comparatorHiHand(CardSet hand1, CardSet hand2)
{
    return compareHand(hand1, hand2) < 0;
}

bool Poker::comparatorLoHand(CardSet hand1, CardSet hand2)
{
    if (hand1 == CardSet("") && hand2 == CardSet(""))
        return false;

    if (hand1 == CardSet(""))
        return true;
    if (hand2 == CardSet(""))
        return false;

    if (hand1.size() != hand2.size())
        throw std::exception("Hand sizes do not match.");

    hand1.sortRank();
    hand2.sortRank();

    if (hand1.cards[0].rank() == Card::Rank::Ace)
    {
        Card ace = hand1.cards[0];
        hand1.remove(hand1.cards[0]);
        hand1.add(ace);
    }

    if (hand2.cards[0].rank() == Card::Rank::Ace)
    {
        Card ace = hand2.cards[0];
        hand2.remove(hand2.cards[0]);
        hand2.add(ace);
    }

    for (int i = 0; i < hand1.size(); i++)
    {
        auto h1Rank = hand1.cards[i].rank();
        auto h2Rank = hand2.cards[i].rank();

        if (i == hand1.size() - 1) // We are on the last card, need to check for potential ace
        {
            if (h1Rank == Card::Rank::Ace)
                return false;
            if (h2Rank == Card::Rank::Ace)
                return true;            
        }
        
        if (h1Rank > h2Rank)
            return true;
        else if (h1Rank < h2Rank)
            return false;        
    }
    return false;
    // return true if hand1 has a higher high card than hand2
    // return true if hand1 is a worse low hand than hand2
}

int Poker::rankHighCard(CardSet hand1, CardSet hand2)
{
    if (hand1.size() != hand2.size())
        throw std::exception("Hand sizes do not match.");
    
    hand1.sortRank();
    hand2.sortRank();

    for (int i = 0; i < hand1.size(); i++)
    {
        auto h1Rank = hand1.cards[i].rank();
        auto h2Rank = hand2.cards[i].rank();
        if (h1Rank > h2Rank)
            return 1;
        else if (h1Rank < h2Rank)
            return -1;
    }
    return 0;
}

int Poker::rankPair(CardSet hand1, CardSet hand2)
{
    if (hand1.size() != hand2.size())
        throw std::exception("Hand sizes do not match.");

    auto h1HighPairRank = Card::Rank::Two;
    auto h2HighPairRank = Card::Rank::Two;

    int h1PairCount = 0;
    int h2PairCount = 0;
    for (auto r : Card::Ranks)
    {
        if (hand1.count(r) == 2)
        {
            h1PairCount += 1;
            if (r > h1HighPairRank)
                h1HighPairRank = r;
        }
        if (hand2.count(r) == 2)
        {
            h2PairCount += 1;
            if (r > h2HighPairRank)
                h2HighPairRank = r;
        }
    }
    if (h1HighPairRank > h2HighPairRank)
        return 1;
    else if (h1HighPairRank < h2HighPairRank)
        return -1;
    else
    {
        for (Card::Suit s : Card::Suits)
        {
            hand1.remove(Card(h1HighPairRank, s));
            hand2.remove(Card(h2HighPairRank, s));
        }
        if (h1PairCount == 2)
            return rankPair(hand1, hand2);
        else
            return rankHighCard(hand1, hand2);
    }
}

int Poker::rankTriple(CardSet hand1, CardSet hand2)
{
    if (hand1.size() != hand2.size())
        throw std::exception("Hand sizes do not match.");

    auto h1TripleRank = Card::Rank::Two;
    auto h2TripleRank = Card::Rank::Two;

    for (auto r : Card::Ranks)
    {
        if (hand1.count(r) == 3)
            h1TripleRank = r;
        if (hand2.count(r) == 3)
            h2TripleRank = r;
    }
    if (h1TripleRank > h2TripleRank)
        return 1;
    else if (h1TripleRank < h2TripleRank)
        return -1;
    else
        return rankHighCard(hand1, hand2);
}

int Poker::rankQuad(CardSet hand1, CardSet hand2)
{
    if (hand1.size() != hand2.size())
        throw std::exception("Hand sizes do not match.");

    auto h1QuadRank = Card::Rank::Two;
    auto h2QuadRank = Card::Rank::Two;

    for (auto r : Card::Ranks)
    {
        if (hand1.count(r) == 4)
            h1QuadRank = r;
        if (hand2.count(r) == 4)
            h2QuadRank = r;
    }
    if (h1QuadRank > h2QuadRank)
        return 1;
    else if (h1QuadRank < h2QuadRank)
        return -1;
    else
        return rankHighCard(hand1, hand2);
}

int Poker::rankStraight(CardSet hand1, CardSet hand2)
{
    int h1Sum = 0;
    int h2Sum = 0;
    for (int i = 0; i < 5; i++)
    {
        h1Sum += (int)hand1.cards[i].rank();
        h2Sum += (int)hand2.cards[i].rank();
    }
    if (hand1.hasRank(Card::Rank::Ace) && hand1.hasRank(Card::Rank::Two))
        h1Sum -= 12;
    if (hand2.hasRank(Card::Rank::Ace) && hand2.hasRank(Card::Rank::Two))
        h2Sum -= 12;

    if (h1Sum > h2Sum)
        return 1;
    else if (h1Sum < h2Sum)
        return -1;
    else
        return 0;
}

template<std::size_t NUM_COMBOS, std::size_t INDEXES_PER_COMBO>
std::vector<CardSet> Poker::combinations(CardSet cards, std::array<std::array<int, INDEXES_PER_COMBO>, NUM_COMBOS> comboArr)
{
    std::vector<CardSet> combo;
    for (auto combination : comboArr)
    {
        CardSet cs{CardSet::Type::Empty};
        for (int index : combination)
        {
            cs.add(cards.cards[index]);
        }
        combo.push_back(cs);
    }

    return combo;
}

std::ostream& operator<<(std::ostream& out, const Poker::Hand& h)
{
    switch (h)
    {
        case Poker::Hand::HighCard:
            out << "High Card";
            break;
        case Poker::Hand::OnePair:
            out << "One Pair";
            break;
        case Poker::Hand::TwoPair:
            out << "Two Pair";
            break;
        case Poker::Hand::ThreeOfAKind:
            out << "Three Of A Kind";
            break;
        case Poker::Hand::Straight:
            out << "Straight";
            break;
        case Poker::Hand::Flush:
            out << "Flush";
            break;
        case Poker::Hand::FullHouse:
            out << "Full House";
            break;
        case Poker::Hand::FourOfAKind:
            out << "Four Of A Kind";
            break;
        case Poker::Hand::StraightFlush:
            out << "Straight Flush";
            break;
    }

    return out;
}
