#include "pch.h"
#include "GameState.h"

void GameState::initVariables()
{
	this->dealtCards = 0;
	this->dealtCards_C = 0;
	this->croupierRound = false;
	this->mouseHeld = false;
	this->game_deck = new GameDeck();
	this->croupier = new Player();
	this->player = new Player();
}

void GameState::initBackground()
{
	this->background.setSize(
		Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/GameState.png"))
	{
		throw "ERROR::GAME_STATE::FAILED_TO_LOAD_BACKGROUND-TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void GameState::initTextures()
{
	string startText = "Resources/Images/Cards/card";
	string endText = ".png";

	for (size_t i = 0; i < 53; i++)
	{
		this->textures["CARD" + to_string(i)].loadFromFile(startText + to_string(i) + endText);
		this->cardShape.setSize(Vector2f(80.f, 130.f));
		this->cardShape.setTexture(&textures["CARD" + to_string(i)]);
		this->cardShape.setRotation(-10.f);
		this->cardsShapes.push_back(this->cardShape);
	}

}

void GameState::initAudio()
{
	string startText = "Resources/Sounds/sound";
	string endText = ".wav";

	for (size_t i = 0; i < 5; i++)
	{
		this->buffer.loadFromFile(startText + to_string(i) + endText);
		this->buffers.push_back(this->buffer);
	}

	for (size_t i = 0; i < 5; i++)
	{
		this->sound.setVolume(0.7f);
		this->sound.setBuffer(this->buffers[i]);
		this->sounds.push_back(this->sound);
	}

	this->sound.setBuffer(this->buffer);

	this->sounds[4].setLoop(true);
	this->sounds[4].play();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-VariableFont_wght.ttf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initText()
{
	this->endText.setFont(this->font);
	this->endText.setCharacterSize(60);
	this->endText.setPosition(Vector2f( 20.f, 502.f));

	for (int i = 0; i < 4; i++)
	{
		this->uiText.setFont(this->font);
		this->uiText.setCharacterSize(20);
		this->uiText.setFillColor(Color::White);
		this->uiText.setOutlineThickness(3.f);
		this->uiText.setOutlineColor(Color::Black);
		this->uiText.setString("0");
		this->texts.push_back(this->uiText);
	}

	this->texts[0].setPosition(Vector2f((this->window->getSize().x / 2.f) - 5.f,
		this->window->getSize().y - 60.f));
	this->texts[1].setPosition(Vector2f(158.f, this->window->getSize().y - 152.f));
	this->texts[2].setPosition(Vector2f(88.f, this->window->getSize().y - 25.f));
	this->texts[3].setPosition(Vector2f(285.f, 225.f));
}

void GameState::initButtons()
{
	this->buttons["EXIT_STATE"] = new Button(this->window->getSize().x - 140.f, 10.f, 120.f, 50.f,
		&this->font, "ESCAPE",
		Color(34, 44, 50, 255), Color(68, 86, 99, 255), Color(43, 55, 63, 255));

	this->buttons["RESET"] = new Button(10.f, 300.f, 120.f, 50.f,
		&this->font, "RESET",
		Color(34, 44, 50, 255), Color(68, 86, 99, 255), Color(43, 55, 63, 255));

	this->buttons["HIT"] = new Button((this->window->getSize().x / 2.f) - 180.f, this->window->getSize().y - 70.f, 120, 50,
		&this->font, "HIT",
		Color(34, 44, 50, 255), Color(68, 86, 99, 255), Color(43, 55, 63, 255));

	this->buttons["STAND"] = new Button((this->window->getSize().x / 2.f) + 60.f, this->window->getSize().y - 70.f, 120, 50,
		&this->font, "STAND",
		Color(34, 44, 50, 255), Color(68, 86, 99, 255), Color(43, 55, 63, 255));

	this->buttons["BET"] = new Button( 128.f, this->window->getSize().y - 80.f, 72.f, 30.f,
		&this->font, "BET",
		Color(34, 44, 50, 255), Color(68, 86, 99, 205), Color(43, 55, 63, 255));

	this->buttons["10"] = new Button(60.f, this->window->getSize().y - 182.f, 58.f, 28.f,
		&this->font, "+10",
		Color(34, 44, 50, 255), Color(68, 86, 99, 205), Color(43, 55, 63, 255));

	this->buttons["50"] = new Button(60.f, this->window->getSize().y - 152.f, 58.f, 28.f,
		&this->font, "+50",
		Color(34, 44, 50, 255), Color(68, 86, 99, 205), Color(43, 55, 63, 255));

	this->buttons["200"] = new Button(60.f, this->window->getSize().y - 122.f, 58.f, 28.f,
		&this->font, "+200",
		Color(34, 44, 50, 255), Color(68, 86, 99, 205), Color(43, 55, 63, 255));

	this->buttons["1000"] = new Button(60.f, this->window->getSize().y - 92.f, 58.f, 28.f,
		&this->font, "+1000",
		Color(34, 44, 50, 255), Color(68, 86, 99, 205), Color(43, 55, 63, 255));
}

void GameState::initPlayers()
{
	// domyslnie wstepne karty beda sie inicjowac po becie

	for (size_t i = 0; i < 2; i++)
	{
		this->sounds[0].play();

		this->player->hit(this->game_deck->my_deck.cards[dealtCards].rank);
		this->croupier->hit(this->game_deck->my_deck.cards[51 - dealtCards].rank);
		dealtCards++; dealtCards_C++;
	}
}

GameState::GameState(RenderWindow* window, stack<State*>* states)
	:State(window, states)
{
	srand(static_cast<unsigned int>(time(NULL)));
	this->initVariables();
	this->initTextures();
	this->initAudio();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initButtons();
}

GameState::~GameState()
{ 
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->player;
	delete this->croupier;
}

void GameState::reset()
{
	this->initVariables();
	this->texts[3].setString("0");
	this->endText.setString("");
	this->player->chips = bufor;
}

void GameState::updateInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		this->endState();
}

void GameState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (this->buttons["RESET"]->isPressed() && this->mouseHeld == false)
		{
			this->bufor = this->player->chips;
			this->reset();
		}
		else if (this->buttons["HIT"]->isPressed() && this->mouseHeld == false && this->croupierRound != true
			&& this->player->betSet == true)
		{
			if (this->player->blackJack != true && this->player->busted != true)
			{
				this->sounds[0].play();
				this->player->hit(this->game_deck->my_deck.cards[dealtCards].rank);
				dealtCards++;
				if (this->player->busted == true)
				{
					this->updateCroupier();
				}
			}
		}
		else if (this->buttons["STAND"]->isPressed() && this->mouseHeld == false && this->croupierRound != true
			&& this->player->betSet == true)
		{
			this->updateCroupier();
		}
		else if (this->buttons["10"]->isPressed() && this->mouseHeld == false && this->player->betSet != true
			&& this->player->chips >= 10)
		{
			this->player->bet(10);
			this->sounds[1].play();
		}
		else if(this->buttons["50"]->isPressed() && this->mouseHeld == false && this->player->betSet != true
			&& this->player->chips >= 50)
		{
			this->player->bet(50);
			this->sounds[1].play();
		}
		else if (this->buttons["200"]->isPressed() && this->mouseHeld == false && this->player->betSet != true
			&& this->player->chips >= 200)
		{
			this->player->bet(200);
			this->sounds[1].play();
		}
		else if (this->buttons["1000"]->isPressed() && this->mouseHeld == false && this->player->betSet != true
			&& this->player->chips >= 1000)
		{
			this->player->bet(1000);
			this->sounds[1].play();
		}
		else if (this->buttons["BET"]->isPressed() && this->mouseHeld == false && this->player->betSet != true 
			&& this->player->chipsbet >= 10)
		{
			this->initPlayers();
			this->player->betSet = true;
		}
		this->mouseHeld = true;
	}
	else
		this->mouseHeld = false;
}

void GameState::updateText()
{
	this->texts[0].setString(to_string(this->player->score));
	this->texts[1].setString(to_string(this->player->chipsbet));
	this->texts[2].setString(to_string(this->player->chips));
	if (this->croupierRound == true)
	{
		this->texts[3].setString(to_string(this->croupier->score));
	}
	else if(this->player->betSet == true)
	{
		this->texts[3].setString(to_string(this->croupier->score 
			- this->croupier->playerCards[1]) + " - ?");
	}
}

void GameState::updateCroupier()
{
	this->croupierRound = true;
	dealtCards_C = croupier->stand(*game_deck);
	if (this->player->busted == true && this->croupier->busted != true ||
		(this->player->score < this->croupier->score && this->croupier->busted != true))
	{
		this->player->updateChips(2);
		this->endText.setString("PRZEGRALES!");
		this->endText.setFillColor(Color::Red);
		this->sounds[3].play();
	}
	else if (this->player->busted == true && this->croupier->busted == true
		|| this->player->score == this->croupier->score)
	{
		this->player->updateChips(1);
		this->endText.setString("REMIS!");
		this->endText.setFillColor(Color::Yellow);
		this->sounds[2].play();
	}
	else
	{
		this->player->updateChips(0);
		this->endText.setString("WYGRALES!");
		this->endText.setFillColor(Color::Green);
		this->sounds[2].play();
	}
}

void GameState::update()
{
	this->updateMousePositions();
	this->updateInput();
	this->updateButtons();
	this->updateText();
}

void GameState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void GameState::renderText(RenderTarget* target)
{
	for (size_t i = 0; i < texts.size(); i++)
	{
		target->draw(this->texts[i]);
	}

	target->draw(this->endText);
}

void GameState::renderCards(RenderTarget* target)
{
	for (int i = 0; i < dealtCards; i++)
	{
		this->cardsShapes[this->game_deck->my_deck.cards[i].cardID].setPosition(Vector2f(
			this->window->getSize().x / 2.f - 130.f + (i * 30.f),
			this->window->getSize().y - 250.f - (i * 20.f)));
		target->draw(cardsShapes[this->game_deck->my_deck.cards[i].cardID]);
	}

	if (croupierRound != false)
	{
		for (int i = 0; i < dealtCards_C; i++)
		{
			this->cardsShapes[this->game_deck->my_deck.cards[51 - i].cardID].setPosition(Vector2f(
				340.f + 82.f * i, 225.f));
			target->draw(cardsShapes[this->game_deck->my_deck.cards[51 - i].cardID]);
		}
	}
	else if(this->player->betSet == true)
	{
		this->cardsShapes[this->game_deck->my_deck.cards[51].cardID].setPosition(Vector2f(
			340.f, 225.f));
		this->cardsShapes[52].setPosition(Vector2f(
			422.f, 225.f));
		target->draw(cardsShapes[this->game_deck->my_deck.cards[51].cardID]);
		target->draw(cardsShapes[52]);
	}
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);
	this->renderCards(target);
	this->renderText(target);
}
