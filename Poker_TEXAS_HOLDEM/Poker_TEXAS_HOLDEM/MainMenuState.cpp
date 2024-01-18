#include "pch.h"
#include "MainMenuState.h"

void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	this->background.setSize(
		Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/MainMenuState.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND-TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-VariableFont_wght.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(322, 470, 380, 80,
		&this->font, "Graj",
		Color(34, 44, 50, 255), Color(68, 86, 99, 255), Color(43, 55, 63, 255));

	this->buttons["EXIT_STATE"] = new Button(322, 570, 380, 80,
		&this->font, "Wyjdz",
		Color(34, 44, 50, 255), Color(68, 86, 99, 255), Color(43, 55 ,63, 255));
}



MainMenuState::MainMenuState(RenderWindow* window, stack<State*>* states)
	:State(window, states)
{
	this->initBackground();
	this->initFonts();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


// UPDATE

void MainMenuState::updateButtons()
{
	/*Aktualizuje przyciski w tym state i obsługuje ich funkcjonalności*/

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->states));
	}
	// wyjdz z gry
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::updateInput()
{
}

void MainMenuState::update()
{
	this->updateMousePositions();
	this->updateButtons();
}

// RENDER

void MainMenuState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);
}
