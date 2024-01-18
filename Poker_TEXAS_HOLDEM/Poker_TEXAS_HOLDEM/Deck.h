#pragma once

#include "GameState.h"
#include "Button.h"
#include "Player.h"

class GameDeck
{
private:
	//----------------------------------------
	//		*** GAME DECK STUFF ***
	//
		enum Rank { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
		enum Suit { CLUBS, HEARTS, SPADES, DIAMONDS };

		struct Card {
			Rank rank = TWO;
			Suit suit = CLUBS;
			int cardID = 0;
			int num_suits = 4;
			int num_rank = 13;
		};

		struct Deck {
			vector<Card> cards;
			int max_deck_size = 52;
		};

	//----------------------------------------
	//		*** INITIALIZE FUNCTIONS ***
	//
		void initDeck(Deck&);
		void shuffleDeck(Deck&);
	//----------------------------------------

public:
	friend class Player;
	friend class GameDeck;
	Deck my_deck;
	//----------------------------------------
	//		*** CONSTRUCTOR / DESTRUCTOR ***
	//
		GameDeck();
		virtual ~GameDeck();
	//----------------------------------------
		void printDeckValues();
};

