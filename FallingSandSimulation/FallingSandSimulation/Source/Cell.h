#include "Enum/Direction.h"
#include "Enum/CellType.h"

#ifndef CELL_H
#define CELL_H

struct Cell
{
	CellType type = CellType::EMPTY;
	Direction direction = Direction::NONE;
};
#endif // !CELL_H


