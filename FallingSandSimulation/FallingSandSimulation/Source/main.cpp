#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>;
#include <random>
#define HEIGHT 200
#define WIDTH 200


using namespace sf;
using namespace std;

enum class Direction
{
	NONE,
	DOWN,
	LEFT,
	RIGHT
};
enum class CellType {
	EMPTY,
	SAND,
	ROCK,
	WATER
};
struct Cell
{
	CellType type = CellType::EMPTY;
	Direction direction = Direction::NONE;
};

void Draw()
{

}

int main()
{
	int scale = 4;
	Cell* cells = new Cell[HEIGHT * WIDTH];
	sf::RenderWindow window(sf::VideoMode(WIDTH * scale, HEIGHT * scale), "SFML works!");



	cells[190 * (WIDTH)+100].type = CellType::ROCK;

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
			cells[100 * (WIDTH)+100].type = CellType::SAND;
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::O))
		{
			cells[100 * (WIDTH)+100].type = CellType::WATER;
		}

		window.clear();

		//UPDATE
		for (auto y = 0; y < HEIGHT - 1; y++)
		{
			for (auto x = 0; x < WIDTH - 1; x++)
			{

				if (cells[y * (WIDTH)+x].type == CellType::EMPTY)
				{
					continue;
				}
				else
				{

					if (cells[y * (WIDTH)+x].type == CellType::SAND)
					{

						//Check down
						if (cells[(y + 1) * (WIDTH)+x].type == CellType::EMPTY)
						{
							cells[(y) * (WIDTH)+x].type = CellType::EMPTY;
							cells[(y + 1) * (WIDTH)+x].type = CellType::SAND;
						}
						else
						{
							//random number
							int random = rand() % 2 + 1;

							if (random == 1)
							{
								//check left
								if (cells[(y + 1) * (WIDTH)+(x - 1)].type == CellType::EMPTY)
								{
									cells[(y) * (WIDTH)+x].type = CellType::EMPTY;
									cells[(y + 1) * (WIDTH)+(x - 1)].type = CellType::SAND;
								}
							}
							else
							{
								//check right
								if (cells[(y + 1) * (WIDTH)+(x + 1)].type == CellType::EMPTY)
								{
									cells[(y) * (WIDTH)+x].type = CellType::EMPTY;
									cells[(y + 1) * (WIDTH)+(x + 1)].type = CellType::SAND;
								}
							}
						
						}
					}


					if (cells[y * (WIDTH)+x].type == CellType::WATER)
					{

						//Check down
						if (cells[(y + 1) * (WIDTH)+x].type == CellType::EMPTY)
						{
							cells[(y) * (WIDTH)+x].type = CellType::EMPTY;
							cells[(y + 1) * (WIDTH)+x].type = CellType::WATER;
						}
						else
						{
							//random number
							int random = rand() % 2 + 1;

							if (random == 1)
							{
								//check left
								if (cells[(y) * (WIDTH)+(x - 1)].type == CellType::EMPTY)
								{
									cells[(y) * (WIDTH)+x].type = CellType::EMPTY;
									cells[(y ) * (WIDTH)+(x - 1)].type = CellType::WATER;
								}
							}
							else
							{
								//check right
								if (cells[(y) * (WIDTH)+(x + 1)].type == CellType::EMPTY)
								{
									cells[(y) * (WIDTH)+x].type = CellType::EMPTY;
									cells[(y ) * (WIDTH)+(x + 1)].type = CellType::WATER;
								}
							}

						}
					}

				}



			}
		}
		//DRAW



		for (auto y = 0; y < HEIGHT; y++)
		{
			for (auto x = 0; x < WIDTH; x++)
			{

				if (cells[y * (WIDTH)+x].type == CellType::EMPTY)
				{
					continue;
				}
				else
				{
					RectangleShape shape(Vector2f(1 * scale, 1 * scale));
					shape.setPosition(Vector2f(x * scale, y * scale));
					if (cells[y * (WIDTH)+x].type == CellType::SAND)
					{
						shape.setFillColor(Color::Yellow);

					}

					if (cells[y * (WIDTH)+x].type == CellType::WATER)
					{
						shape.setFillColor(Color::Blue);

					}
					else if (cells[y * (WIDTH)+x].type == CellType::ROCK)
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
