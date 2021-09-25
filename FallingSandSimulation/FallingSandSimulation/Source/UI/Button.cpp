#include "Button.h"

Button::Button(std::string text, sf::Vector2f size, int x, int y, int characterSize, sf::Color buttonColor, sf::Color textColor, sf::Font& font)
{
	this->text.setString(text);
	this->text.setFillColor(textColor);
	this->text.setFont(font);
	this->text.setCharacterSize(characterSize);
	this->text.setPosition(x, y);

	button.setSize(size);
	button.setFillColor(buttonColor);
	button.setPosition(x, y);
}

Button::~Button()
{
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}

bool Button::isMouseOver(int x, int y)
{
	if (button.getTextureRect().contains(x, y))
	{
		this->text.Bold;
		return true;
	}
	else
	{
		return false;
	}
}
