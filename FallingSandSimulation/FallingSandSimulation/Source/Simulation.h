#pragma once
#include "Cell.h"
#include <SFML/Graphics.hpp>

#include "Enum/CellType.h";
class Simulation
{
public:
	 int width;
	 int height;

private:
	Cell* cells = nullptr;
	std::vector<sf::Vector2f> changes;

public:
	Simulation(int width, int height);
	~Simulation();

	void UpdateSimulation();
	void SetCell(int x, int y, CellType type);
	void MoveCell(int x, int y, int targetX, int targetY);
	void CommitCells();
	CellType GetCellType(int x, int y);

};

