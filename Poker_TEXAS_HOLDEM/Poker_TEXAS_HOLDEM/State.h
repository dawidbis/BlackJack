#pragma once
#include "Button.h"

class State
{
private:


protected:
	stack<State*>* states;
	RenderWindow* window;
	bool quit;

	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	// Zasoby
	map<string, Texture> textures;

public:
	State(RenderWindow* window, stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	void endState();

	virtual void updateMousePositions();
	virtual void updateInput() = 0;
	virtual void update() = 0;
	virtual void render(RenderTarget* target = nullptr) = 0;
};
