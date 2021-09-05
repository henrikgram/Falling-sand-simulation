#pragma once
#include "Cell.h"
#include "Enum/CellType.h";
class Simulation
{
public:
	 int width;
	 int height;

private:
	Cell* cells = nullptr;

public:
	Simulation(int width, int height);
	~Simulation();

	void UpdateSimulation();
	void SetCell(int x, int y, CellType type);
	CellType GetCellType(int x, int y);

};

