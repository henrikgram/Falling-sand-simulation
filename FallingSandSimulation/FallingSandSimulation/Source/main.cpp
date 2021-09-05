#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "Cell.h"
#include "Enum/CellType.h";

#include <chrono>
#include <thread>
#include <iostream>;
#include <random>
#define HEIGHT 200
#define WIDTH 200


using namespace sf;
using namespace std;

//enum class Direction
//{
//	NONE  = 0b00000000,
//	DOWN  = 0b00000001,
//	LEFT  = 0b00000010,
//	RIGHT = 0b00000100
//};
//enum class CellType {
//	EMPTY,
//	SAND,
//	ROCK,
//	WATER
//};
//struct Cell
//{
//	CellType type = CellType::EMPTY;
//	Direction direction = Direction::NONE;
//};

void Draw()
{

}

int main()
{
	int scale = 4;
	//Cell* cells = new Cell[HEIGHT * WIDTH];
	sf::RenderWindow window(sf::VideoMode(WIDTH * scale, HEIGHT * scale), "PowderGame clone");
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

		if (Keyboard::isKeyPressed(Keyboard::Key::P))
		{
			sim->SetCell(100, 100, CellType::SAND);
			//cells[100 * (WIDTH)+100].type = CellType::SAND;
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::O))
		{
			sim->SetCell(100, 100, CellType::WATER);
			//cells[100 * (WIDTH)+100].type = CellType::WATER;
		}

		window.clear();

		
		//DRAW
		sim->UpdateSimulation();



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

	return 0;
}
