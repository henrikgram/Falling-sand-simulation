#pragma once
#include "SFML/Graphics.hpp"
/// <summary>
/// Object with a rectangle shape, which is clickable and highlightable
/// </summary>
class Button
{
private:
	bool isSelected;
	bool isLeft;
	sf::RectangleShape button;
	sf::Text text;
public:

	Button(std::string text, sf::Vector2f size, int x, int y, int characterSize, sf::Color buttonColor, sf::Color textColor,sf::Font& font);
	virtual ~Button();
	void Draw(sf::RenderWindow& window);
	bool isMouseOver(int x, int y);
	void Highlight();
	void Select(bool isLeft = true);
	void DeSelect();
	void ReturnToOriginalColor();
	std::string GetText();
	void SetText(std::string text);
	bool GetIsSelected();
	bool GetIsLeft();


};

