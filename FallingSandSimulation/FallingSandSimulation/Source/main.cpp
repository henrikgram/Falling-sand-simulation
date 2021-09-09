#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "Cell.h"
#include <chrono>
#include <algorithm>
#include "Enum/CellType.h";
#include <Windows.h>
#include <chrono>
#include <thread>
#include <iostream>;
#include <random>
#include <vector>
#include <cmath>
#define HEIGHT 200
#define WIDTH 200


using namespace sf;
using namespace std;
using namespace std::chrono;

int scale = 4;
sf::RenderWindow window(sf::VideoMode(WIDTH* scale, HEIGHT* scale), "PowderGame clone");

void Draw(Simulation* sim)
{

	for (auto y = HEIGHT; y >= 0; y--)
	{
		for (auto x = WIDTH; x >= 0; x--)
		{

			CellType type = sim->GetCellType(x, y);

			if (type == CellType::EMPTY)
			{
				continue;
			}
			else
			{
				RectangleShape shape(Vector2f(1 * scale, 1 * scale));
				shape.setPosition(Vector2f(x * scale, y * scale));
				if (type == CellType::SAND)
				{
					shape.setFillColor(Color::Yellow);

				}

				if (type == CellType::WATER)
				{
					shape.setFillColor(Color::Blue);

				}
				else if (type == CellType::ROCK)
				{
					shape.setFillColor(Color::Red);
				}

				window.draw(shape);
			}



		}
	}


	window.display();
}

vector<Vector2i> TraverseMatrix(Vector2f pos1, Vector2f pos2)
{
	// y = mx+ b
	bool isHorisontal = true;
	int distanceX = abs(pos2.x - pos1.x);
	int distanceY = abs(pos2.y - pos1.y);

	int distance;

	if (distanceX > distanceY)
	{
		isHorisontal = true;
		distance = distanceX;
	}
	else
	{
		isHorisontal = false;
		distance = distanceY;
	}

	float slope = (pos2.y - pos1.y) / (pos2.x - pos1.x);

	vector<Vector2i> points;

	for (int i = 0; i <= distance; i++)
	{
		if (isHorisontal)
		{
			points.push_back(Vector2i(i, round(pos1.y + (slope * i))));
		}
		else
		{
			points.push_back(Vector2i(round(pos1.x + (slope * i)),i));
		}
		
	}

	return points;
}

int main()
{
	int counter = 0;
	Vector2f lastFramePos(0, 0);

	CellType brushMode = CellType::SAND;

	//Cell* cells = new Cell[HEIGHT * WIDTH];
	
	Simulation* sim = new Simulation(HEIGHT, WIDTH);
	
	sim->SetCell(100, 150, CellType::ROCK);
	//cells[190 * (WIDTH)+100].type = CellType::ROCK;

	while (window.isOpen())
	{

		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{

			sim->SetCell(Mouse::getPosition(window).x/scale, Mouse::getPosition(window).y / scale, brushMode);

			/*vector<Vector2i> points = TraverseMatrix(lastFramePos, Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y));

			for (int i = 0; i < points.size(); i++)
			{
				sim->SetCell(points[i].x / scale, points[i].y / scale, brushMode);
			}*/
			
		}
		

		if (Keyboard::isKeyPressed(Keyboard::Key::S))
		{
			brushMode = CellType::SAND;
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::W))
		{
			brushMode = CellType::WATER;
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::R))
		{
			brushMode = CellType::ROCK;
		}



	
		window.clear();

		auto start = high_resolution_clock::now();
		
		//DRAW
		sim->UpdateSimulation();

		auto stop = high_resolution_clock::now();

		auto duration = duration_cast<std::chrono::microseconds>(stop - start);

		std::cout << "Time taken by Update(): "
				<< duration.count() << " microseconds" << endl;

		Draw(sim);

		counter++;
		lastFramePos.x = Mouse::getPosition(window).x;
		lastFramePos.y = Mouse::getPosition(window).y;

		if (counter >= 2)
		{
			counter = 0;
		}
	
	}

	return 0;
}
