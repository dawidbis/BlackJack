#include "pch.h"
#include "Game.h"
#include "MainMenuState.h"

//
// 
//		--> *** FUNKCJE INICJALIZUJĄCE *** <--
//

// INIT VARIABLES
//---------------------------------------------
void Game::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
}

// INIT WINDOW:
// 
// 	   - tworzy okno SFML używając window.ini
//---------------------------------------------
void Game::initWindow()
{
	ifstream ifs("Config/window.ini");
	this->videoModes = VideoMode::getFullscreenModes();

	string title = "None";
	VideoMode window_bounds = VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open())
	{
		getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}

	ifs.close();

	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen)
		this->window = new RenderWindow(VideoMode(window_bounds), title, Style::Fullscreen, windowSettings);
	else
		this->window = new RenderWindow(VideoMode(window_bounds), title, Style::Titlebar | Style::Close, windowSettings);

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

// INIT STATES
//---------------------------------------------
void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->states));
}

//---------------------------------------------
// 
//		--> *** KONSTRUKTOR I DESTRUKTOR *** <--
//
Game::Game()
{
	this->initWindow();
	this->initStates();
}

Game::~Game() 
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}

}
//---------------------------------------------
// 
//			--> *** FUNKCJE *** <--
//

// UPDATE SFML EVENTS
//---------------------------------------------
void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == Event::Closed)
			this->window->close();
	}
}

//	UPDATE
//---------------------------------------------
void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update();

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	// koniec działania programu
	else
	{
		this->window->close();
	}
}

//	RENDER
//---------------------------------------------
void Game::render()
{
	this->window->clear();

	// Render items
	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

// RUN
//---------------------------------------------
void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}
