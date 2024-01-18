#pragma once

#include "State.h"
#include "Button.h"
#include "Player.h"
#include "Deck.h"

class GameState :
    public State
{
private:
	//----------------------------------------
	//			*** GUI ***
	//
		vector<SoundBuffer> buffers;
		SoundBuffer buffer;
		vector<Sound> sounds;
		Sound sound;	
		Texture backgroundTexture;
		RectangleShape background;
		Font font;
		vector<Text> texts;
		Text uiText, endText;
		map<string, Button*> buttons;
		vector<RectangleShape> cardsShapes;
		RectangleShape cardShape;
		bool mouseHeld;
	//----------------------------------------
	//		*** GAME LOGIC ***
	//
		GameDeck *game_deck;
		Player *player, *croupier;
		int dealtCards;
		int dealtCards_C;
		bool croupierRound;
		//
		int bufor;

	//----------------------------------------
	//		*** INITIALIZE FUNCTIONS ***
	//
		void initVariables();
		void initBackground();
		void initTextures();
		void initAudio();
		void initFonts();
		void initText();
		void initButtons();
		void initPlayers();
	//----------------------------------------


public:
	friend class Player;
	friend class GameDeck;
	//----------------------------------------
	//		*** CONSTRUCTOR / DESTRUCTOR ***
	//
		GameState(RenderWindow* window, stack<State*>* states);
		virtual ~GameState();
	//----------------------------------------

	//----------------------------------------
	//		*** UPDATE FUNCTIONS ***
	//
		void reset();
		void updateInput();
		void updateButtons();
		void updateText();
		void updateCroupier();
		void update();
	//----------------------------------------

	//----------------------------------------
	//		*** RENDER FUNCTIONS ***
	//
		void renderButtons(RenderTarget* target = nullptr);
		void renderText(RenderTarget* target = nullptr);
		void renderCards(RenderTarget* target = nullptr);
		void render(RenderTarget* target = nullptr);
	//----------------------------------------
};

