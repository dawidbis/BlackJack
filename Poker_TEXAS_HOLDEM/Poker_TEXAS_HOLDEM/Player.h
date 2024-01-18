#pragma once

#include "GameState.h"
#include "Button.h"
#include "Deck.h"

class Player
{
private:
	void initVariables();
public:
	friend class GameState;
	friend class GameDeck;
	Player();
	virtual ~Player();

	vector<int> playerCards;
	bool busted;
	bool blackJack;
	bool betSet;
	int score;
	int acesNumber;
	int chips;
	int chipsbet;
	
	void hit(int card_val);
	int stand(GameDeck g_deck);
	void updateScore();
	void bet(int chip_val);
	void updateChips(int result);
};

