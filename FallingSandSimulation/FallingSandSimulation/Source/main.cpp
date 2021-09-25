#include <SFML/Graphics.hpp>

#include "Simulation.h"
#include "Elements/Concrete Elements/Sand.h"
#include "Elements/Concrete Elements/Water.h"
#include "Elements/Concrete Elements/Rock.h"
#include "Elements/Concrete Elements/Smoke.h"
#include "UI/Button.h"
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
Context context;
sf::RenderWindow window(sf::VideoMode(200 * scale, 250 * scale), "SFML works!");
sf::Font font;

int prevX;
int prevY;

int width = 200;
int height = 200;
int offset = 7;
RectangleShape ui(Vector2f(width* scale, 50 * scale));
sf::Text SandText;
sf::Text MousePositionText;
sf::Text BrushSizeText;
sf::Text ElementCountText;
sf::Text WaterText;

Button* sandButton;
Button* waterButton;
Button* smokeButton;
Button* rockButton;

VertexArray CursorSize(LineStrip, 5);


string toString(int integer)
{
	char numstr[10]; // enough to hold all numbers up to 32-bits
	sprintf_s(numstr, "%i", integer);
	return numstr;
}

void DrawUI()
{
	window.draw(ui);

	
	window.draw(ElementCountText);


	float x = Mouse::getPosition(window).x;
	float y = Mouse::getPosition(window).y;

	//TODO: odd numbers dosen't work completely
	CursorSize[0].position = Vector2f(x - brushSize * scale / 2, y + brushSize / 2 * scale);
	CursorSize[1].position = Vector2f(x + brushSize * scale / 2, y + brushSize / 2 * scale);
	CursorSize[2].position = Vector2f(x + brushSize * scale / 2, y - brushSize / 2 * scale);
	CursorSize[3].position = Vector2f(x - brushSize * scale / 2, y - brushSize / 2 * scale);
	CursorSize[4].position = Vector2f(x - brushSize * scale / 2, y + brushSize / 2 * scale);



	window.draw(CursorSize);


	MousePositionText.setString("X: " + toString(x / scale) + " Y: " + toString(y / scale));
	window.draw(MousePositionText);

	BrushSizeText.setString("BrushSize: " + toString(brushSize));
	window.draw(BrushSizeText);

	sandButton->Draw(window);
	waterButton->Draw(window);
	rockButton->Draw(window);


}

void Draw(Simulation* sim)
{

	//Simulation
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{

			ElementTag type = sim->GetElementTag(x, y);

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
	if (true)
	{
		sandButton = new Button("Sand", Vector2f(80, 35), 0, width * scale, 30, Color(50, 50, 50), Color::Yellow, font);


		waterButton = new Button("Water", Vector2f(80, 35), 0, width * scale + offset * scale + offset, 30, Color(50, 50, 50), Color::Blue, font);


		rockButton = new Button("Rock", Vector2f(80, 35), 0, width * scale + offset * scale *2 + offset, 30, Color(50, 50, 50), Color(100,100,100), font);

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


		ui.setFillColor(Color(50, 50, 50));
		ui.setPosition(Vector2f(0, width * scale));

	}




	Simulation* sim = new Simulation(width, width);
	//sim->ReplaceElement(new Sand(150, 100));
	//sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::SAND,150,100));

	//sim->AddElementsBetweenPoints(100, 199,100, 10, ElementTag::SAND);


	while (window.isOpen())
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
					if (sandButton->isMouseOver(x, y))
					{

						if (Event::MouseButtonPressed)
						{
							//sandButton->Highlight();
						}
					}
					else
					{
						sandButton->ReturnToOriginalColor();
					}

				}
			}
				break;

			case(sf::Event::MouseButtonPressed):

				sandButton->Select();
				break;
			


			}
		}




		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			int x = Mouse::getPosition(window).x / scale;
			int y = Mouse::getPosition(window).y / scale;

			if (!sim->OutOfBounds(x, y))
			{
				sim->AddElementsBetweenPoints(x, y, prevX, prevY, ElementTag::SAND, brushSize);
			}

		}

		if (Mouse::isButtonPressed(Mouse::Button::Right))
		{
			int x = Mouse::getPosition(window).x / scale;
			int y = Mouse::getPosition(window).y / scale;

			if (x < width && x > 0 && y < 200 && y > 0)
			{
				for (int yy = 0; yy < brushSize; yy++)
				{
					for (int xx = 0; xx < brushSize; xx++)
					{

						sim->ReplaceElement(new Rock(x + xx - brushSize / 2, y + yy - brushSize / 2));

					}

				}
			}

		}

		window.clear();
		auto start = high_resolution_clock::now();
		//sim->DeleteElements();

		prevX = Mouse::getPosition(window).x / scale;
		prevY = Mouse::getPosition(window).y / scale;

		sim->UpdateSimulation();

		auto stop = high_resolution_clock::now();

		auto duration = duration_cast<std::chrono::microseconds>(stop - start);

		std::cout << "Time taken by Update(): " << duration.count() << " microseconds" << std::endl;

		auto start2 = high_resolution_clock::now();

		Draw(sim);

		auto stop2 = high_resolution_clock::now();

		auto duration2 = duration_cast<std::chrono::microseconds>(stop2 - start2);

		//
		//std::cout << "Time taken by Draw(): "
		//	<< duration2.count() << " microseconds" << std::endl;



	}

	return 0;
}