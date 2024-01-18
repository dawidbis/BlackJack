#pragma once

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
private:
	short unsigned buttonState;

	RectangleShape shape;
	Font* font;
	Text text;

	Color idleColor;
	Color hoverColor;
	Color activeColor;

public:
	Button(float x, float y, float width, float height,
		Font* font, string text,
		Color idleColor, Color hoverColor, Color activeColor);
	~Button();

	// Stan przycisku
	const bool isPressed() const;

	// Funkcje
	void update(const Vector2f mousePos);
	void render(RenderTarget* target);
};
