#pragma once
#include "SFML/Graphics.hpp"
class Button
{
public:
	Button(std::string text, sf::Vector2f size, int x, int y, int characterSize, sf::Color buttonColor, sf::Color textColor,sf::Font& font);
	~Button();
	void Draw(sf::RenderWindow& window);
	bool isMouseOver(int x, int y);
	void Highlight();
	void Select();
	void DeSelect();
	void ReturnToOriginalColor();
	sf::RectangleShape button;
	sf::Text text;
};

