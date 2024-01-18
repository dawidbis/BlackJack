#pragma once

#include"Button.h"

class State;

class Game
{
private:
	//$-----------------------------------------------------
		// 
		//	*** ZMIENNE ***
		//
	RenderWindow* window;
	Event sfEvent;
	vector<VideoMode> videoModes;
	ContextSettings windowSettings;
	bool fullscreen;

	stack<State*> states;

	//--------------------------------------------------
	// 
	//	*** FUNKCJE INICJALIZUJĄCE ***
	//
	void initVariables();
	void initWindow();
	void initStates();

public:
	//$-----------------------------------------------------
		// 
		//	*** KONSTRUKTOR I DESTRUKTOR ***
		//
	Game();
	virtual ~Game();

	//--------------------------------------------------
	// 
	//	*** FUNKCJE ***
	//

	// Update
	void updateSFMLEvents();
	void update();

	// Render
	void render();

	// Core
	void run();
};

