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
	if (button.getGlobalBounds().contains(x,y))
	{
		this->text.Bold;
		return true;
	}
	else
	{
		return false;
	}
}

void Button::Highlight()
{
	button.setFillColor(sf::Color(80, 80, 80));
}

void Button::Select()
{
	button.setOutlineThickness(1);
	button.setOutlineColor(sf::Color::White);
}

void Button::DeSelect()
{
	button.setOutlineThickness(0);
}

void Button::ReturnToOriginalColor()
{
	button.setFillColor(sf::Color(50, 50, 50));
}
