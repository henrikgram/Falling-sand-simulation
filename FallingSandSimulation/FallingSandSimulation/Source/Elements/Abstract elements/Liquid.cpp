#include "Liquid.h"

Liquid::Liquid(int posX, int posY, int dispersionRate) : Element(posX,posY)
{
	this->dispersionRate = dispersionRate;
}

Liquid::~Liquid()
{
}

void Liquid::UpdateElement(Simulation* sim)
{
	if (sim->GetElementTag(posX, posY + 1) == ElementTag::EMPTY)
	{
		SwapPositions(sim, posX, posY + 1);
	}
	else
	{
		int direction = rand() % 2 + 1;

		for (int i = 1; i <= dispersionRate; i++)
		{
			if (direction == 1)
			{
				if (sim->GetElementTag(posX - i, posY) == ElementTag::EMPTY)
				{
					SwapPositions(sim, posX - i, posY);
				}
			}
			else
			{
				if (sim->GetElementTag(posX + i, posY) == ElementTag::EMPTY)
				{
					SwapPositions(sim, posX + i, posY);
				}
			}
		}

		
	}
}
