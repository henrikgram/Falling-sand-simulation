#include "Liquid.h"

Liquid::Liquid(int posX, int posY, int dispersionRate) : Element(posX,posY)
{
	this->dispersionRate = dispersionRate;
	abstractTag = AbstractTag::LIQUID;
	velocityY = 1;
}


bool Liquid::IsValidMove(Simulation* sim, int dstX, int dstY)
{
	AbstractTag element = sim->GetAbstractType(dstX, dstY);

	if (element == AbstractTag::EMPTY)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}


Liquid::~Liquid()
{
}

//TODO: add diagonal support.
bool Liquid::UpdateElement(Simulation* sim)
{
	if (Element::UpdateElement(sim))
	{
		return true;
	}


	if (MoveTo(sim, posX, posY + velocityY))
	{
		AccelerateY(sim->GetGravity());
	}
	else
	{
		velocityY = 1;
		int direction = rand() % 2 + 1;
		

		//Check all the way in the choosen direction, until it finds a not empty element

		if (direction == 1)
		{
			MoveTo(sim, posX + dispersionRate + velocityY, posY);
		}
		else
		{
			MoveTo(sim, posX - dispersionRate - velocityY, posY);
		}

	}

	return false;
}
