#include "pch.h"
#include "Player.h"

void Player::initVariables()
{
	this->busted = false;
	this->blackJack = false;
	this->betSet = false;
	this->score = 0;
	this->acesNumber = 0;
	this->chipsbet = 0;
	this->chips = 1000;
}

Player::Player()
{
	this->initVariables();
}

Player::~Player()
{

}

void Player::hit(int card_val)
{
	if (card_val >= 8)
	{
		if (card_val == 12)
		{
			this->playerCards.push_back(11);
			this->acesNumber++;
		}
		else
			this->playerCards.push_back(10);
	}
	else
		this->playerCards.push_back(card_val + 2);

	this->updateScore();
}

int Player::stand(GameDeck g_deck)
{
	int count = 2;

	while (this->blackJack != true && this->busted != true && this->score <= 16)
	{
		this->hit(g_deck.my_deck.cards[51 - count].rank);
		count++;
	}

	return count;
}

void Player::updateScore()
{
	score = 0;

	for (size_t i = 0; i < playerCards.size(); i++)
	{
		score += playerCards[i];
	}

	if (score >= 21)
	{
		if (score == 21)
			this->blackJack = true;
		else if (acesNumber > 0 && score > 21)
		{
			for (int i = 0; i < acesNumber; i++)
			{
				if (score <= 21)
					break;
				else
					this->score -= 10;
			}

			if(this->score == 21)
				this->blackJack = true;
			else if(this->score > 21)
				this->busted = true;
		}
		else
			this->busted = true;
	}

	//cout << " SUMA: " << score << endl; debug
}

void Player::bet(int chip_val)
{
	chips -= chip_val;
	chipsbet += chip_val;
}

void Player::updateChips(int result)
{
	switch (result)
	{
	case 0:
		chips += chipsbet * 2;
		break;
		
	case 1:
		chips += chipsbet;
		break;

	case 2:
		chips -= 0;
		if (chips < 0)
			chips = 0;
		break;
	}
}
