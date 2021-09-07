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
#define HEIGHT 200
#define WIDTH 200


using namespace sf;
using namespace std;
using namespace std::chrono;

int scale = 4;
sf::RenderWindow window(sf::VideoMode(WIDTH* scale, HEIGHT* scale), "PowderGame clone");

void Draw(Simulation* sim)
{

	for (auto y = 0; y < HEIGHT; y++)
	{
		for (auto x = 0; x < WIDTH; x++)
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

int main()
{

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
			sim->SetCell(sf::Mouse::getPosition(window).x / scale, sf::Mouse::getPosition(window).y / scale, brushMode);
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

	}

	return 0;
}
