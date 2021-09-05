#include "Simulation.h"
#include <random>

Simulation::Simulation(int width, int height)
{
	this->width = width;
	this->height = height;
	cells = new Cell[width * height];
	//cells[190 * (width)+100].type = CellType::ROCK;
}

void Simulation::UpdateSimulation()
{
	for (auto y = height - 1; y > 0; y--)
	{
		for (auto x = width - 1; x > 0; x--)
		{

			if (cells[y * (width)+x].type == CellType::EMPTY)
			{
				continue;
			}
			else
			{
				if (cells[y * (width)+x].type == CellType::SAND)
				{

					//Check down
					if (cells[(y + 1) * (width)+x].type == CellType::EMPTY)
					{
						cells[(y) * (width)+x].type = CellType::EMPTY;
						cells[(y + 1) * (width)+x].type = CellType::SAND;
					}
					else
					{
						//random number
						int random = rand() % 2 + 1;

						if (random == 1)
						{
							//check left
							if (cells[(y + 1) * (width)+(x - 1)].type == CellType::EMPTY)
							{
								cells[(y) * (width)+x].type = CellType::EMPTY;
								cells[(y + 1) * (width)+(x - 1)].type = CellType::SAND;
							}
						}
						else
						{
							//check right
							if (cells[(y + 1) * (width)+(x + 1)].type == CellType::EMPTY)
							{
								cells[(y) * (width)+x].type = CellType::EMPTY;
								cells[(y + 1) * (width)+(x + 1)].type = CellType::SAND;
							}
						}

					}
				}


				if (cells[y * (width)+x].type == CellType::WATER)
				{

					//Check down
					if (cells[(y + 1) * (width)+x].type == CellType::EMPTY)
					{
						cells[(y) * (width)+x].type = CellType::EMPTY;
						cells[(y + 1) * (width)+x].type = CellType::WATER;
					}
					else
					{
						//random number
						int random = rand() % 2 + 1;

						if (random == 1)
						{
							//check left
							if (cells[(y) * (width)+(x - 1)].type == CellType::EMPTY)
							{
								cells[(y) * (width)+x].type = CellType::EMPTY;
								cells[(y) * (width)+(x - 1)].type = CellType::WATER;
							}
						}
						else
						{
							//check right
							if (cells[(y) * (width)+(x + 1)].type == CellType::EMPTY)
							{
								cells[(y) * (width)+x].type = CellType::EMPTY;
								cells[(y) * (width)+(x + 1)].type = CellType::WATER;
							}
						}

					}
				}

			}



		}
	}
}

void Simulation::SetCell(int x, int y, CellType type)
{
	cells[y * (width)+x].type = type;
}

CellType Simulation::GetCellType(int x, int y)
{
	return cells[y * (width)+x].type;
}
