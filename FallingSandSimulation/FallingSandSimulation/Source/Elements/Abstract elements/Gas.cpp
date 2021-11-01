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
	if (SpecialBehavior(sim))
	{
		return;
	}

	if (IsValidMove(sim, posX, posY - 1))
	{
		SwapPositions(sim, posX, posY - 1);
	}


	else
	{
		int direction = rand() % 2 + 1;

		if (direction == 1)
		{
			MoveTo(sim, posX - 1, posY);
		}
		else
		{
			MoveTo(sim, posX + 1, posY);
		}
	}
}

bool Gas::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
		return false;
}

bool Gas::SpecialBehavior(Simulation* sim)
{
	return false;
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
