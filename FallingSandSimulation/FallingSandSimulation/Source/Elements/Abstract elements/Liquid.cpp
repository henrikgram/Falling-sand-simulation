#include "Liquid.h"

Liquid::Liquid(int posX, int posY, int dispersionRate) : Element(posX,posY)
{
	this->dispersionRate = dispersionRate;
	abstractTag = AbstractTag::LIQUID;
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
void Liquid::UpdateElement(Simulation* sim)
{
	//TODO: this should work in the later checks
	if (CheckSurroundingElementsForAffect(sim, posX, posY))
	{
		return;
	}

	if (SpecialBehavior(sim))
	{
		return;
	}
	
	if (IsValidMove(sim, posX, posY + 1))
	{
		MoveTo(sim, posX, posY + 1);
	}
	else
	{
		int direction = rand() % 2 + 1;
		

		//Check all the way in the choosen direction, until it finds a not empty element

		if (direction == 1)
		{
			MoveTo(sim, posX + dispersionRate, posY);
		}
		else
		{
			MoveTo(sim, posX - dispersionRate, posY);
		}

	}
}
