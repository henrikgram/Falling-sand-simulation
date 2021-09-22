#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "Elements/Concrete Elements/Sand.h"
#include "Elements/Concrete Elements/Water.h"
#include <Windows.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>
#include<string>

using namespace std;
using namespace std::chrono;


int scale = 4;
int brushSize = 0;
sf::RenderWindow window(sf::VideoMode(200 * scale, 250 * scale), "SFML works!");
sf::Font font;


int width = 200;
int height = 200;
int offset = 7;
RectangleShape ui(Vector2f(width* scale, 50 * scale));
sf::Text SandText;
sf::Text MousePositionText;
sf::Text ElementCountText;
sf::Text WaterText;

string toString(int integer)
{
	char numstr[10]; // enough to hold all numbers up to 32-bits
	sprintf_s(numstr, "%i", integer);
	return numstr;
}

void DrawUI()
{
	window.draw(ui);

	window.draw(SandText);
	window.draw(WaterText);
	window.draw(ElementCountText);

	float x = Mouse::getPosition(window).x / scale;
	float y = Mouse::getPosition(window).y / scale;
	
	MousePositionText.setString("X: " + toString(x) + " Y: "+ toString(y));
	window.draw(MousePositionText);
	if (ui.getTextureRect().contains(Mouse::getPosition()));
	{
	}

	
}

void Draw(Simulation* sim)
{
	//Simulation
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{

			ElementTag type = sim->GetElementTag(x, y);
			//ElementTag type = ElementTag::SAND;


			if (type == ElementTag::EMPTY)
			{
				continue;
			}

			else
			{
				RectangleShape shape(Vector2f(1 * scale, 1 * scale));
				shape.setPosition(Vector2f(x * scale, y * scale));
				shape.setFillColor(Color::Yellow);

				if (type == ElementTag::SAND)
				{
					shape.setFillColor(Color::Yellow);

				}
				else if (type == ElementTag::WATER)
				{
					shape.setFillColor(Color::Blue);
				}
				else
				{
					int pik = 4;
				}

				window.draw(shape);


			}
		}


	}

	//UI
	ElementCountText.setString(toString(sim->Elements));
	DrawUI();



	window.display();
}

int main()
{
	if (!font.loadFromFile("C:\\Users\\Henrik\\Documents\\GitHub\\Falling-sand-simulation\\FallingSandSimulation\\Minecraft.ttf"))
	{
		cout << "C:\\Users\Henrik\Documents\GitHub\Falling-sand-simulation\FallingSandSimulation\Minecraft.ttf";
		system("pause");
	}

	SandText.setFont(font);
	SandText.setFillColor(Color::Yellow);
	SandText.setString("Sand");
	SandText.setPosition(Vector2f(0, width * scale));

	WaterText.setFont(font);
	WaterText.setFillColor(Color::Blue);
	WaterText.setString("Water");
	WaterText.setPosition(Vector2f(0, width * scale + offset * scale + offset));

	MousePositionText.setFont(font);
	MousePositionText.setFillColor(Color::White);
	MousePositionText.setString("Sand");
	MousePositionText.setPosition(Vector2f(width*scale-200, width * scale));

	ElementCountText.setFont(font);
	ElementCountText.setFillColor(Color::White);
	ElementCountText.setString("Sand");
	ElementCountText.setPosition(Vector2f(width * scale - 200, width * scale + offset * scale));

	ui.setFillColor(Color(50, 50, 50));
	ui.setPosition(Vector2f(0, width * scale));


	Simulation* sim = new Simulation(width, width);
	sim->ReplaceElement(new Sand(199, 100));


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Event::MouseWheelMoved)
		{

		}

		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			int x = Mouse::getPosition(window).x / scale;
			int y = Mouse::getPosition(window).y / scale;

			if (x < width && x > 0 && y < 200 && y > 0)
			{
				sim->ReplaceElement(new Sand(x, y));
				sim->ReplaceElement(new Sand(x+1, y));
				sim->ReplaceElement(new Sand(x+1, y+1));
				sim->ReplaceElement(new Sand(x, y+1));
			}
		
		}
		if (Mouse::isButtonPressed(Mouse::Button::Right))
		{
			int x = Mouse::getPosition(window).x / scale;
			int y = Mouse::getPosition(window).y / scale;

			if (x < width && x > 0 && y < 200 && y > 0)
			{
					sim->ReplaceElement(new Water(x, y));
			}
		
		}
	
		window.clear();
		auto start = high_resolution_clock::now();
		//sim->DeleteElements();
		sim->UpdateSimulation();

		auto stop = high_resolution_clock::now();

		auto duration = duration_cast<std::chrono::microseconds>(stop - start);

		std::cout << "Time taken by Update(): "
			<< duration.count() << " microseconds" << std::endl;


		Draw(sim);
		
		
	}

	return 0;
}