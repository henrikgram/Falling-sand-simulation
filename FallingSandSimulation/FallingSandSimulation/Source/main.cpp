#include <SFML/Graphics.hpp>

#include "Simulation.h"
#include "Elements/Concrete Elements/Sand.h"
#include "Elements/Concrete Elements/Water.h"
#include "Elements/Concrete Elements/Rock.h"
#include "Elements/Concrete Elements/Smoke.h"
#include "UI/ElementButton.h"
#include <Windows.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>
#include<string>


using namespace std;
using namespace std::chrono;



int scale = 4;
int brushSize = 2;
ElementTag leftBrushMode = ElementTag::SAND;
ElementTag rightBrushMode = ElementTag::EMPTY;
Context context;
sf::RenderWindow window(sf::VideoMode(200 * scale, 250 * scale), "SFML works!");
sf::Font font;
Simulation* sim;
int prevX;
int prevY;

int width = 200;
int height = 200;
int offset = 10;

RectangleShape uiArea(Vector2f(width* scale, 50 * scale));
sf::Text SandText;
sf::Text MousePositionText;
sf::Text BrushSizeText;
sf::Text ElementCountText;
sf::Text WaterText;


vector<Button*>* buttons = new vector<Button*>();


VertexArray CursorSize(LineStrip, 5);

/// <summary>
/// Converts int to string
/// </summary>
/// <param name="integer"></param>
/// <returns></returns>
string toString(int integer)
{
	char numstr[10]; // enough to hold all numbers up to 32-bits
	sprintf_s(numstr, "%i", integer);
	return numstr;
}

/// <summary>
/// UI related draw calls
/// </summary>
void DrawUI()
{
	float x = Mouse::getPosition(window).x;
	float y = Mouse::getPosition(window).y;


	//Cursor square
	//TODO: odd numbers dosen't work completely
	CursorSize[0].position = Vector2f(x - brushSize * scale / 2, y + brushSize / 2 * scale);
	CursorSize[1].position = Vector2f(x + brushSize * scale / 2, y + brushSize / 2 * scale);
	CursorSize[2].position = Vector2f(x + brushSize * scale / 2, y - brushSize / 2 * scale);
	CursorSize[3].position = Vector2f(x - brushSize * scale / 2, y - brushSize / 2 * scale);
	CursorSize[4].position = Vector2f(x - brushSize * scale / 2, y + brushSize / 2 * scale);

	//Dont draw on the ui area
	if (y / scale < 200)
	{
		window.draw(CursorSize);
	}


	MousePositionText.setString("X: " + toString(x / scale) + " Y: " + toString(y / scale));
	BrushSizeText.setString("BrushSize: " + toString(brushSize));
	ElementCountText.setString(toString(sim->Elements));

	window.draw(uiArea);
	window.draw(ElementCountText);
	window.draw(MousePositionText);
	window.draw(BrushSizeText);

	for (auto i : *buttons)
	{
		i->Draw(window);
	}


}

/// <summary>
/// Draws the elements from the simulation
/// </summary>
void Draw()
{
	//Simulation
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			ElementTag type = sim->GetElementType(x, y);

			if (type == ElementTag::EMPTY)
			{
				continue;
			}
			else
			{
				RectangleShape shape(Vector2f(1 * scale, 1 * scale));
				shape.setPosition(Vector2f(x * scale, y * scale));
				shape.setFillColor((sim->GetElement(x, y)->GetColor()));

				window.draw(shape);
			}
		}

	}

	//UI
	DrawUI();
	window.display();
}

/// <summary>
/// Intializes all buttons etc.
/// </summary>
void Setup()
{
	//LoadFont
	if (!font.loadFromFile("C:\\Users\\Henrik\\Documents\\GitHub\\Falling-sand-simulation\\FallingSandSimulation\\Minecraft.ttf"))
	{
		cout << "C:\\Users\Henrik\Documents\GitHub\Falling-sand-simulation\FallingSandSimulation\Minecraft.ttf";
		system("pause");
	}

	//Buttons
	buttons->push_back(new ElementButton("Sand", Vector2f(100, 35), 0, width * scale + offset, 30, Color(50, 50, 50), Color::Yellow, font, ElementTag::SAND));
	buttons->push_back(new ElementButton("Water", Vector2f(100, 35), 0, width * scale + offset * scale + offset, 30, Color(50, 50, 50), Color::Blue, font, ElementTag::WATER));
	buttons->push_back(new ElementButton("Rock", Vector2f(100, 35), 0, width * scale + offset * scale * 2 + offset, 30, Color(50, 50, 50), Color(100, 100, 100), font, ElementTag::ROCK));
	buttons->push_back(new ElementButton("Smoke", Vector2f(100, 35), 0, width * scale + offset * scale * 3 + offset, 30, Color(50, 50, 50), Color(180, 180, 180), font, ElementTag::SMOKE));

	buttons->push_back(new ElementButton("Erase", Vector2f(100, 35), 0, width * scale + offset * scale * 4 + offset, 30, Color(50, 50, 50), Color(0, 0, 0), font, ElementTag::EMPTY));
	buttons->push_back(new Button("Clear", Vector2f(100, 35), 120, width * scale + offset * scale * 4 + offset, 30, Color(50, 50, 50), Color(0, 0, 0), font));

	buttons->push_back(new ElementButton("Lava", Vector2f(100, 35), 120, width * scale + offset, 30, Color(50, 50, 50), Color::Red, font, ElementTag::LAVA));
	buttons->push_back(new ElementButton("Vapor", Vector2f(100, 35), 120, width * scale + offset * scale + offset, 30, Color(50, 50, 50), Color::White, font, ElementTag::VAPOR));

	//Making sure the default
	(*buttons)[0]->Select();
	(*buttons)[4]->Select(false);

	MousePositionText.setFont(font);
	MousePositionText.setFillColor(Color::White);
	MousePositionText.setString("Sand");
	MousePositionText.setPosition(Vector2f(width * scale - 200, width * scale));

	ElementCountText.setFont(font);
	ElementCountText.setFillColor(Color::White);
	ElementCountText.setString("Sand");
	ElementCountText.setPosition(Vector2f(width * scale - 200, width * scale + offset * scale));

	BrushSizeText.setFont(font);
	BrushSizeText.setFillColor(Color::White);
	BrushSizeText.setString("Sand");
	BrushSizeText.setPosition(Vector2f(width * scale - 200, width * scale + offset * 2 * scale));

	uiArea.setFillColor(Color(50, 50, 50));
	uiArea.setPosition(Vector2f(0, width * scale));


}

void HandleInput()
{
	//clrscr();
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case(sf::Event::Closed):
			window.close();
			break;

		case(sf::Event::MouseWheelScrolled):

			if (event.mouseWheelScroll.wheel == Mouse::VerticalWheel)
			{
				if (brushSize <= 1)
				{
					if (event.mouseWheelScroll.delta > 0)
					{
						brushSize += event.mouseWheelScroll.delta;
					}
				}
				else
				{
					brushSize += event.mouseWheelScroll.delta;
				}

			}
			break;

		case(sf::Event::MouseMoved):
		{
			int x = Mouse::getPosition(window).x;
			int y = Mouse::getPosition(window).y;

			if (y / scale > 195)
			{
				for (auto i : *buttons)
				{
					if (i->isMouseOver(x, y))
					{
						i->Highlight();
					}
					else
					{
						i->ReturnToOriginalColor();
					}
				}

			}
		}
		break;

		case(sf::Event::MouseButtonPressed):

			int x = Mouse::getPosition(window).x;
			int y = Mouse::getPosition(window).y;
			for (auto i : *buttons)
			{
				if (i->isMouseOver(x, y))
				{
					bool isLeft;
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						isLeft = true;
						ElementButton* e = dynamic_cast<ElementButton*>(i);
						if (e != nullptr)
						{
							leftBrushMode = e->GetElement();
							i->Select();
						}

						if (i->GetText() == "Clear")
						{
							delete sim;
							sim = nullptr;

							sim = new Simulation(width, height);

						}
					
					}
					else
					{
						//TODO: look here for performance, it may be cursed
						ElementButton* e = dynamic_cast<ElementButton*>(i);
						if (e != nullptr)
						{
							rightBrushMode = e->GetElement();
							isLeft = false;
							i->Select(false);
						}

					
					}



					for (auto j : *buttons)
					{
						if (j->GetIsSelected() == true && j->GetIsLeft() == isLeft)
						{
							if (i == j)
							{
								continue;
							}
							else

							{
								j->DeSelect();

							}
						}
					}
				}

			}
			break;



		}
	}




	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		int x = Mouse::getPosition(window).x / scale;
		int y = Mouse::getPosition(window).y / scale;

		if (!sim->OutOfBounds(x, y))
		{
			sim->AddElementsBetweenPoints(x, y, prevX, prevY, leftBrushMode, brushSize);
		}

	}

	if (Mouse::isButtonPressed(Mouse::Button::Right))
	{
		int x = Mouse::getPosition(window).x / scale;
		int y = Mouse::getPosition(window).y / scale;

		if (!sim->OutOfBounds(x, y))
		{
			sim->AddElementsBetweenPoints(x, y, prevX, prevY, rightBrushMode, brushSize);
		}

	}

}

int main()
{
	Setup();

	sim = new Simulation(width, width);

	while (window.isOpen())
	{
		//auto start3 = high_resolution_clock::now();

		HandleInput();
		window.clear();

		//auto stop3 = high_resolution_clock::now();
		//auto duration3 = duration_cast<std::chrono::microseconds>(stop3 - start3);
		//std::cout << "Time taken by Input: " << duration3.count() << " microseconds" << std::endl;

		auto start = high_resolution_clock::now();
	
		//Used for keeping track of the previous frames mouse positions, so it can be connected when drawing.
		prevX = Mouse::getPosition(window).x / scale;
		prevY = Mouse::getPosition(window).y / scale;

		sim->UpdateSimulation();

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Time taken by Update(): " << duration.count() << " microseconds" << std::endl;

		//auto start2 = high_resolution_clock::now();

		Draw();

		//auto stop2 = high_resolution_clock::now();
		//auto duration2 = duration_cast<std::chrono::microseconds>(stop2 - start2);


	}

	return 0;
}