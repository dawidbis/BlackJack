#pragma once

#include "State.h"
#include "GameState.h"

class MainMenuState
	:public State
{
private:
	// Zmienne
	Texture backgroundTexture;
	RectangleShape background;
	Font font;

	map<string, Button*> buttons;

	// Funkcje
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();

public:
	MainMenuState(RenderWindow* window, stack<State*>* states);
	virtual ~MainMenuState();

	// Funkcje
	void updateButtons();
	void updateInput();
	void update();
	void renderButtons(RenderTarget* target = nullptr);
	void render(RenderTarget* target = nullptr);
};
