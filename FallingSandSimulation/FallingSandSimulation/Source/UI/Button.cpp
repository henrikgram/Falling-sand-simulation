#include "Button.h"

/// <summary>
/// 
/// </summary>
/// <param name="text">Button text</param>
/// <param name="size">Size of the buttons rectangle</param>
/// <param name="x">X position</param>
/// <param name="y">Y position</param>
/// <param name="characterSize"></param>
/// <param name="buttonColor">Fill color</param>
/// <param name="textColor"></param>
/// <param name="font"></param>
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

/// <summary>
/// Returns true if the position is in the button rectangles area
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
bool Button::isMouseOver(int x, int y)
{
	if (button.getGlobalBounds().contains(x,y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// Changes the the fill color to a brighter color
/// </summary>
void Button::Highlight()
{
	button.setFillColor(sf::Color(80, 80, 80));
}

/// <summary>
/// Selects the button
/// </summary>
/// <param name="isLeft">If it's left or right selected</param>
void Button::Select(bool isLeft)
{
	isSelected = true;
	this->isLeft = isLeft;
	button.setOutlineThickness(1);

	if (isLeft)
	{
		button.setOutlineColor(sf::Color(0, 162, 255));
	}
	else
	{
		button.setOutlineColor(sf::Color(255, 154, 0));

	}
	
}

void Button::DeSelect()
{
	isSelected = false;
	button.setOutlineThickness(0);
}

void Button::ReturnToOriginalColor()
{
	button.setFillColor(sf::Color(50, 50, 50));
}

bool Button::GetIsSelected()
{
	return isSelected;
}

bool Button::GetIsLeft()
{
	return isLeft;
}

std::string Button::GetText()
{
	return text.getString();
}

void Button::SetText(std::string text)
{
	this->text.setString(text);
}

