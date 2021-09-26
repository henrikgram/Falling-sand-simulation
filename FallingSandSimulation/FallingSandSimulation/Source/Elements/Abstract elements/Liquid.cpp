#include "Liquid.h"

Liquid::Liquid(int posX, int posY, int dispersionRate) : Element(posX,posY)
{
	this->dispersionRate = dispersionRate;
}

Liquid::~Liquid()
{
}

//TODO: add diagonal support.
void Liquid::UpdateElement(Simulation* sim)
{
	//if under is empty go here first
	if (sim->GetElementTag(posX, posY + 1) == ElementTag::EMPTY)
	{
		SwapPositions(sim, posX, posY + 1);
	}
	else
	{
		int direction = rand() % 2 + 1;

		//Check all the way in the choosen direction, until it finds a not empty element

		//TODO maybe this is cursed
		if (dispersionRate > 1)
		{
			for (int i = 1; i <= dispersionRate; i++)
			{
				if (direction == 1)
				{
					//If it's at the end of the loop, and still hasn't found a filled element, then it just chooses this one.
					if (sim->GetElementTag(posX - i, posY) == ElementTag::EMPTY && i < dispersionRate)
					{
						continue;
					}
					else
					{
						SwapPositions(sim, posX - (i - 1), posY);

						break;
					}
				}
				else
				{
					if (sim->GetElementTag(posX + i, posY) == ElementTag::EMPTY && i < dispersionRate)
					{
						continue;
					}
					else
					{
						SwapPositions(sim, posX + (i - 1), posY);

						break;
					}
				}
			}
		}
		else
		{
			if (direction == 1)
			{
				if (sim->GetElementTag(posX - 1, posY) == ElementTag::EMPTY )
				{
					SwapPositions(sim, posX - 1, posY);
				}
			}
			else
			{
				if (sim->GetElementTag(posX + 1, posY) == ElementTag::EMPTY )
				{
					SwapPositions(sim, posX + 1, posY);
				}
			}
		}
		

		
	}
}
