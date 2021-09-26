#pragma once
#include "Button.h"
#include "../Enum/ElementTag.h"

/// <summary>
/// Button but also contains a element type
/// </summary>
class ElementButton : virtual public Button
{
private:
	ElementTag element;
public:
	ElementButton(std::string text, sf::Vector2f size, int x, int y, int characterSize, sf::Color buttonColor, sf::Color textColor, sf::Font& font, ElementTag element);
	ElementTag GetElement();
	virtual ~ElementButton();
};

