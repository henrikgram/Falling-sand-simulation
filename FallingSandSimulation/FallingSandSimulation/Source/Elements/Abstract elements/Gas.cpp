#include "Gas.h"

Gas::Gas(int posX, int posY) : Element(posX, posY)
{
}

Gas::~Gas()
{
}

void Gas::UpdateElement(Simulation* sim)
{
	if (sim->GetElementTag(posX, posY - 1) == ElementTag::EMPTY)
	{
		SwapPositions(sim, posX, posY - 1);
	}
	else
	{
		int direction = rand() % 2 + 1;

		if (direction == 1)
		{
			if (sim->GetElementTag(posX - 1, posY) == ElementTag::EMPTY)
			{
				SwapPositions(sim, posX - 1, posY);
			}
		}
		else
		{
			if (sim->GetElementTag(posX + 1, posY) == ElementTag::EMPTY)
			{
				SwapPositions(sim, posX + 1, posY);
			}
		}
	}
}
