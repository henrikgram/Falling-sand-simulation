#include "Liquid.h"

Liquid::Liquid(int posX, int posY, int dispersionRate) : Element(posX,posY)
{
	this->dispersionRate = dispersionRate;
	abstractTag = AbstractTag::LIQUID;
}

bool Liquid::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	return false;
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

bool Liquid::SpecialBehavior(Simulation* sim)
{
	return false;
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
		SwapPositions(sim, posX, posY + 1);
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
