#include <iostream>
#include "CardSet.h"
#include "Poker.h"
#include "Timer.h"

using namespace std;

void printResults(int wins, int ties, int losses, int trials);
void texasHoldEm();
void omahaHoldEm();
void omahaHoldEmHiLo();
int readInt(string message);
int getPlayers();
string getCards(string message, int numCards);

int main()
{
	omahaHoldEmHiLo();
}

void omahaHoldEmHiLo()
{
	cout << "Playing Omaha Hold Em Hi/Lo 8" << endl;
	int numPlayers = getPlayers();

	while (true)
	{
		cout << "----------------------------------------" << endl;
		vector<CardSet> hands;
		CardSet table;

		// Pre-Flop
		string cardStr = getCards("Enter your four cards.", 4);
		if (cardStr == "quit")
			break;
		if (cardStr == "next")
			continue;

		hands.push_back(CardSet(cardStr));

		for (int i = 0; i < numPlayers - 1; i++)
		{
			hands.push_back(CardSet());
		}

		Poker::omahaHoldEmHiLoHandProbability(hands, table);

		// Flop
		cardStr = getCards("Enter the 3 flop cards.", 3);;
		if (cardStr == "quit")
			break;
		if (cardStr == "next")
			continue;

		table += CardSet(cardStr);

		Poker::omahaHoldEmHiLoHandProbability(hands, table);

		// Turn
		cardStr = getCards("Enter the turn card.", 1);
		if (cardStr == "quit")
			break;
		if (cardStr == "next")
			continue;

		table += CardSet(cardStr);

		Poker::omahaHoldEmHiLoHandProbability(hands, table);

		// River
		cardStr = getCards("Enter the river card", 1);
		if (cardStr == "quit")
			break;
		if (cardStr == "next")
			continue;

		table += CardSet(cardStr);

		Poker::omahaHoldEmHiLoHandProbability(hands, table);
	}
}

void omahaHoldEm()
{
	cout << "Playing Omaha Hold Em" << endl;
	int numPlayers = getPlayers();

	while (true)
	{
		cout << "----------------------------------------" << endl;
		vector<CardSet> hands;
		CardSet table;

		// Pre-Flop
		string cardStr = getCards("Enter your four cards.", 4);
		if (cardStr == "quit")
			break;
		if (cardStr == "next")
			continue;

		hands.push_back(CardSet(cardStr));

		for (int i = 0; i < numPlayers - 1; i++)
		{
			hands.push_back(CardSet());
		}

		int wins, ties, losses, trials;
		tie(wins, ties, losses, trials) = Poker::omahaHoldEmHandProbability(hands, table);
		printResults(wins, ties, losses, trials);

		// Flop
		cardStr = getCards("Enter the 3 flop cards.", 3);;
		if (cardStr == "quit")
			break;
		if (cardStr == "next")
			continue;

		table += CardSet(cardStr);

		tie(wins, ties, losses, trials) = Poker::omahaHoldEmHandProbability(hands, table);
		printResults(wins, ties, losses, trials);

		// Turn
		cardStr = getCards("Enter the turn card.", 1);
		if (cardStr == "quit")
			break;
		if (cardStr == "next")
			continue;

		table += CardSet(cardStr);

		tie(wins, ties, losses, trials) = Poker::omahaHoldEmHandProbability(hands, table);
		printResults(wins, ties, losses, trials);

		// River
		cardStr = getCards("Enter the river card", 1);
		if (cardStr == "quit")
			break;
		if (cardStr == "next")
			continue;

		table += CardSet(cardStr);

		tie(wins, ties, losses, trials) = Poker::omahaHoldEmHandProbability(hands, table);
		printResults(wins, ties, losses, trials);
	}
}

void texasHoldEm()
{
	cout << "Playing Texas Hold Em" << endl;
	int numPlayers = getPlayers();

	while (true)
	{
		cout << "----------------------------------------" << endl;
		vector<CardSet> hands;
		CardSet table;

		// Pre-Flop
		string cardStr = getCards("Enter your two cards.", 2);
		if (cardStr == "quit")
			break;
		if (cardStr == "next")
			continue;

		hands.push_back(CardSet(cardStr));

		for (int i = 0; i < numPlayers - 1; i++)
		{
			hands.push_back(CardSet());
		}

		int wins, ties, losses, trials;
		tie(wins, ties, losses, trials) = Poker::texasHoldEmHandProbability(hands, table);
		printResults(wins, ties, losses, trials);

		// Flop
		cardStr = getCards("Enter the 3 flop cards.", 3);;
		if (cardStr == "quit")
			break;
		if (cardStr == "next")
			continue;

		table += CardSet(cardStr);

		tie(wins, ties, losses, trials) = Poker::texasHoldEmHandProbability(hands, table);
		printResults(wins, ties, losses, trials);

		// Turn
		cardStr = getCards("Enter the turn card.", 1);
		if (cardStr == "quit")
			break;
		if (cardStr == "next")
			continue;

		table += CardSet(cardStr);

		tie(wins, ties, losses, trials) = Poker::texasHoldEmHandProbability(hands, table);
		printResults(wins, ties, losses, 10000);

		// River
		cardStr = getCards("Enter the river card", 1);
		if (cardStr == "quit")
			break;
		if (cardStr == "next")
			continue;

		table += CardSet(cardStr);

		tie(wins, ties, losses, trials) = Poker::texasHoldEmHandProbability(hands, table);
		printResults(wins, ties, losses, trials);
	}
}

void printResults(int wins, int ties, int losses, int trials)
{
	cout << endl;
	cout << "Wins:\t" << wins * 100. / trials << "%\t" << wins << "\t/ " << trials << "\t" << endl;
	cout << "Ties:\t" << ties * 100. / trials << "%\t" << ties << "\t/ " << trials << "\t" <<  endl;
	cout << "Loss:\t" << losses * 100. / trials << "%\t" << losses << "\t/ " << trials << "\t" << endl;
	cout << endl;
}

string getCards(string message, int numCards)
{
	string cardStr;
	while (true)
	{
		cout << message << endl;
		cout << "Card(s): ";
		string hand;
		getline(cin, hand);

		if (hand == "quit" || hand == "next")
			return hand;

		try
		{
			CardSet cards(hand);
			if (cards.size() != numCards)
				throw exception();
			cardStr = hand;
			break;
		}
		catch (exception e)
		{
			cout << "Invalid card string. Make sure to enter exactly " << numCards << " cards." << endl;
		}
	}

	return cardStr;
}

int getPlayers()
{
	int numPlayers;
	while (numPlayers = readInt("Enter the number of players: "))
	{
		if (numPlayers >= 2 && numPlayers <= 10)
			break;
		else
			cout << "Must be between 2 and 10" << endl;
	}
	return numPlayers;
}

int readInt(string prompt)
{
	int num;
	while (true)
	{
		cout << prompt;
		if (cin >> num)
			break;
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return num;
}