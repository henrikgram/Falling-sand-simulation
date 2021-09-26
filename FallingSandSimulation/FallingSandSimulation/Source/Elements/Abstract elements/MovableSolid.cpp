#include "MovableSolid.h"
//#include <random>

MovableSolid::MovableSolid(int posX, int posY) : Solid(posX, posY), Element(posX, posY)
{
}

MovableSolid::~MovableSolid()
{
}

void MovableSolid::UpdateElement(Simulation* sim)
{
	ElementTag ElementUnder = sim->GetElementTag(posX, posY + 1);
	if (ElementUnder == ElementTag::EMPTY || ElementUnder == ElementTag::WATER)
	{
		SwapPositions(sim, posX, posY + 1);
	}
	else
	{
		int direction = rand() % 2 + 1;

		if (direction == 1)
		{
			ElementTag ElementRight = sim->GetElementTag(posX - 1, posY + 1);

			if (ElementRight == ElementTag::EMPTY || ElementRight == ElementTag::WATER)
			{
				SwapPositions(sim, posX - 1, posY + 1);
			}
		}
		else
		{

			ElementTag ElementLeft = sim->GetElementTag(posX + 1, posY + 1);
			if (ElementLeft == ElementTag::EMPTY || ElementLeft == ElementTag::WATER)
			{
				SwapPositions(sim, posX + 1, posY + 1);
			}
		}
	}
}
