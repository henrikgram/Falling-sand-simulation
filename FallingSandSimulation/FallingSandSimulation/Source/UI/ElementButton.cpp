#include "ElementButton.h"

ElementButton::ElementButton(std::string text, sf::Vector2f size, int x, int y, int characterSize, sf::Color buttonColor, sf::Color textColor, sf::Font& font, ElementTag element) : Button(text,size,x,y,characterSize,buttonColor,textColor,font)
{
	this->element = element;
}

ElementTag ElementButton::GetElement()
{
	return element;
}

ElementButton::~ElementButton()
{
}
