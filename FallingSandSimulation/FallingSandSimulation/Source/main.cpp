#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "UI/ElementButton.h"

#include <Windows.h>
#include <chrono>
#include <iostream>
#include <algorithm>
#include<string>

int scale = 4;
int brushSize = 2;
ElementTag leftBrushMode = ElementTag::SAND;
ElementTag rightBrushMode = ElementTag::EMPTY;

int width = 200;
int height = 200;

sf::RenderWindow window(sf::VideoMode(width * scale, (height + (height /4)) * scale), "Falling sand simulation");


sf::Font font;
Simulation* sim;
int prevX;
int prevY;


int offset = 10;
bool isPaused = false;

RectangleShape uiArea(Vector2f(width* scale, height/4 * scale));
sf::Text SandText;
sf::Text MousePositionText;
sf::Text BrushSizeText;
sf::Text ElementCountText;
sf::Text WaterText;

std::vector<Vertex> image;
std::vector<Vertex> imageRect;
std::vector<sf::Drawable> GUI;
std::vector<Button*>* buttons = new std::vector<Button*>();


VertexArray CursorSize(LineStrip, 5);

/// <summary>
/// Converts int to string
/// </summary>
/// <param name="integer"></param>
/// <returns></returns>
std::string toString(int integer)
{
	char numstr[10]; // enough to hold all numbers up to 32-bits
	sprintf_s(numstr, "%i", integer);
	return numstr;
}

void AddQuad(int x, int y)
{
	sf::Vertex topLeft;
	sf::Vertex topRight;
	sf::Vertex bottomLeft;
	sf::Vertex bottomRight;

	float onScreenX = x * scale;
	float onScreenY = y * scale;

	topLeft.position = { onScreenX, onScreenY };
	topRight.position = { onScreenX + scale, onScreenY };
	bottomLeft.position = { onScreenX + scale, onScreenY + scale };
	bottomRight.position = { onScreenX, onScreenY + scale };

	image.push_back(topLeft);
	image.push_back(topRight);
	image.push_back(bottomLeft);
	image.push_back(bottomRight);
}

void SetColor(int x, int y, sf::Color color)
{
	int index = (y * width + x) * scale;

	for (int i = 0; i < scale; i++)
	{
		image[index + i].color = color;
	}
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
	if (y / scale < height)
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
				SetColor(x, y, sf::Color(0, 0, 0));
			}
			else
			{
				SetColor(x, y, sim->GetElement(x, y)->GetColor());
			}
		
		}

	}

	//window.draw(image.data(), imageRect.size(), sf::Quads);
	window.draw(image.data(), image.size(), sf::Quads);

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
	//TODO: relative path
	if (!font.loadFromFile("Minecraft.ttf"))
	{
		std::cout << "Minecraft.ttf";
		system("pause");
	}
	

	//Buttons
	buttons->push_back(new ElementButton("Sand",	Vector2f(100, 35), 0, width * scale , 30, Color(50, 50, 50), Color::Yellow, font, ElementTag::SAND));
	buttons->push_back(new ElementButton("Water",	Vector2f(100, 35), 0, width * scale + offset * scale , 30, Color(50, 50, 50), Color::Blue, font, ElementTag::WATER));
	buttons->push_back(new ElementButton("Rock",	Vector2f(100, 35), 0, width * scale + offset * scale * 2 , 30, Color(50, 50, 50), Color(100, 100, 100), font, ElementTag::ROCK));
	buttons->push_back(new ElementButton("Smoke",   Vector2f(100, 35), 0, width * scale + offset * scale * 3 , 30, Color(50, 50, 50), Color(180, 180, 180), font, ElementTag::SMOKE));

	buttons->push_back(new ElementButton("Erase",	Vector2f(100, 35), 0, width * scale + offset * scale * 4 , 30, Color(50, 50, 50), Color(0, 0, 0), font, ElementTag::EMPTY));
	buttons->push_back(new Button("Clear",			Vector2f(100, 35), 120, width * scale + offset * scale * 4 , 30, Color(50, 50, 50), Color(0, 0, 0), font));
	buttons->push_back(new Button("Pause",			Vector2f(100, 35), 120 * 2, width * scale + offset * scale * 4 , 30, Color(50, 50, 50), Color(0, 0, 0), font));

	buttons->push_back(new ElementButton("Lava",    Vector2f(100, 35), 120, width * scale  , 30, Color(50, 50, 50), Color::Red, font, ElementTag::LAVA));
	buttons->push_back(new ElementButton("Vapor",   Vector2f(100, 35), 120, width * scale + offset * scale , 30, Color(50, 50, 50), Color::White, font, ElementTag::VAPOR));
	buttons->push_back(new ElementButton("Acid",    Vector2f(100, 35), 120, width * scale + offset * scale * 2  , 30, Color(50, 50, 50), Color::Green, font, ElementTag::ACID));
	buttons->push_back(new ElementButton("OutFlow", Vector2f(100, 35), 120, width * scale + offset * scale * 3  , 30, Color(50, 50, 50), Color::Magenta, font, ElementTag::OUTFLOW));

	buttons->push_back(new ElementButton("Dirt",    Vector2f(100, 35), 120 * 2, width * scale , 30, Color(50, 50, 50), Color(82,42,16), font, ElementTag::DIRT));
	buttons->push_back(new ElementButton("Coal",	Vector2f(100, 35), 120 * 2, width * scale + offset * scale , 30, Color(50, 50, 50), Color(0,0,0,200), font, ElementTag::COAL));
	buttons->push_back(new ElementButton("TNT",		Vector2f(100, 35), 120 * 2, width * scale + offset * scale *2 , 30, Color(50, 50, 50), Color(255, 0, 0), font, ElementTag::TNT));
	buttons->push_back(new ElementButton("InFlow",  Vector2f(100, 35), 120 * 2, width * scale + offset * scale * 3 , 30, Color(50, 50, 50), Color::Cyan, font, ElementTag::INFLOW));

	buttons->push_back(new ElementButton("Wood",	Vector2f(100, 35), 120 * 3, width * scale , 30, Color(50, 50, 50), Color(82*2, 42*2, 16*2), font, ElementTag::WOOD));
	buttons->push_back(new ElementButton("Snow",	Vector2f(100, 35), 120 * 3, width * scale + offset * scale , 30, Color(50, 50, 50), Color(250, 250, 255), font, ElementTag::SNOW));
	buttons->push_back(new ElementButton("Grass",	 Vector2f(100, 35),   120 * 3, width * scale + offset * scale *2, 30, Color(50, 50, 50), Color(188, 252, 119), font, ElementTag::GRASS));

	//Making sure the default
	(*buttons)[0]->Select();
	(*buttons)[4]->Select(false);

	MousePositionText.setFont(font);
	MousePositionText.setFillColor(Color::White);
	MousePositionText.setString("Sand");
	MousePositionText.setPosition(Vector2f(width * scale - width * scale /4, width * scale));

	ElementCountText.setFont(font);
	ElementCountText.setFillColor(Color::White);
	ElementCountText.setString("Sand");
	ElementCountText.setPosition(Vector2f(width * scale - width * scale / 4, width * scale + offset * scale));

	BrushSizeText.setFont(font);
	BrushSizeText.setFillColor(Color::White);
	BrushSizeText.setString("Sand");
	BrushSizeText.setPosition(Vector2f(width * scale - width * scale / 4, width * scale + offset * 2 * scale));

	uiArea.setFillColor(Color(50, 50, 50));
	uiArea.setPosition(Vector2f(0, width * scale));

	
	//reserves the space
	image.reserve((width * height) * scale);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (scale!= 1)
			{
				AddQuad(x, y);
			}
			else
			{
				sf::Vertex pixel;
				pixel.position = sf::Vector2f(x, y);
				image.push_back(pixel);
			}
			
		
		}
	}
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

			if (y / scale > height)
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
		{
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
						else if (i->GetText() == "Pause")
						{
							isPaused = true;
							i->SetText("Resume");

						}
						else if (i->GetText() == "Resume")
						{
							isPaused = false;
							i->SetText("Pause");
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

		case(sf::Event::KeyPressed):
		{

			if (event.key.code == sf::Keyboard::Right)
			{
				if (isPaused)
				{

					auto start = std::chrono::high_resolution_clock::now();

					sim->UpdateSimulation(50,150);

					auto stop = std::chrono::high_resolution_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
					std::cout << "Time taken by Update(): " << duration.count() << " microseconds" << std::endl;
				}
			}

		}

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
	
	window.setFramerateLimit(60);
	sim = new Simulation(width, height);
	
	while (window.isOpen())
	{
		HandleInput();

		window.clear();

		prevX = Mouse::getPosition(window).x / scale;
		prevY = Mouse::getPosition(window).y / scale;

		auto start = std::chrono::high_resolution_clock::now();

		if (!isPaused)
		{
			sim->Update();
			sim->ResetSimulation();
		}

		Draw();

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Time taken by Update(): " << duration.count() << " microseconds" << std::endl;
	}

	return 0;
}