#include "pch.h"
#include "Deck.h"

void GameDeck::initDeck(Deck& deck)
{
	Card card; int counter = 0;
	for (int suit = 0; suit < card.num_suits; suit++)
	{
		for (int rank = 0; rank < card.num_rank; rank++)
		{
			card.cardID = counter;
			card.suit = Suit(suit);
			card.rank = Rank(rank);
			deck.cards.push_back(card);
			counter++;
		}
	}
}

void GameDeck::shuffleDeck(Deck& deck)
{
	Deck shuffled;
	while (!deck.cards.empty())
	{
		size_t rand_index = rand() % deck.cards.size();
		shuffled.cards.push_back(deck.cards[rand_index]);
		deck.cards.erase(deck.cards.begin() + rand_index);
	}

	deck = shuffled;
}

GameDeck::GameDeck()
{
	this->initDeck(my_deck);
	this->shuffleDeck(my_deck);
}

GameDeck::~GameDeck()
{

}

void GameDeck::printDeckValues()
{
	for (size_t i = 0; i < 52; i++)
	{
		cout << my_deck.cards[i].cardID << " ";
	}
}
