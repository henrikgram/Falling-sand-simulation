#include "Gas.h"

Gas::Gas(int posX, int posY,int health) : Element(posX, posY, health)
{
	abstractTag = AbstractTag::GAS;
}

Gas::~Gas()
{
}

void Gas::UpdateElement(Simulation* sim)
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
	
	//Element::UpdateElement(sim);

	if (IsValidMove(sim, posX, posY - 1))
	{
		MoveTo(sim, posX, posY - 1);
	}
	else
	{
		int direction = rand() % 2 + 1;


		//Check all the way in the choosen direction, until it finds a not empty element

		if (direction == 1)
		{
			MoveTo(sim, posX + 1, posY);
		}
		else
		{
			MoveTo(sim, posX - 1, posY);
		}

	}
}



bool Gas::IsValidMove(Simulation* sim, int dstX, int dstY)
{
	AbstractTag element = sim->GetAbstractType(dstX, dstY);

	if (element == AbstractTag::EMPTY || element == AbstractTag::LIQUID)
	{
		return true;
	}
	else if (element == AbstractTag::GAS)
	{
		if (this->density > sim->GetElement(dstX, dstY)->GetDensity())
		{
			return true;
		}
	}
	return false;
}
