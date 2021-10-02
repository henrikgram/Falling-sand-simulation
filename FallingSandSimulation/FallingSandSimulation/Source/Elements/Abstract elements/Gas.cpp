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

	AbstractTag ElementUnder = sim->GetAbstractType(posX, posY - 1);
	if (ElementUnder == AbstractTag::GAS)
	{
		if (this->density > sim->GetElement(posX, posY - 1)->GetDensity())
		{
			SwapPositions(sim, posX, posY - 1);
		}
	}
	if (ElementUnder == AbstractTag::EMPTY || ElementUnder == AbstractTag::LIQUID)
	{
		SwapPositions(sim, posX, posY - 1);
		//AffectOtherElement(sim, posX, posY - 1);
	}

	else
	{
		int direction = rand() % 2 + 1;

		if (direction == 1)
		{
			AbstractTag ElementRight = sim->GetAbstractType(posX - 1, posY);

			if (ElementRight == AbstractTag::EMPTY || ElementRight == AbstractTag::LIQUID || ElementRight == AbstractTag::GAS)
			{
				SwapPositions(sim, posX - 1, posY);
			}
		}
		else
		{
			AbstractTag ElementLeft = sim->GetAbstractType(posX + 1, posY);

			if (ElementLeft == AbstractTag::EMPTY || ElementLeft == AbstractTag::LIQUID || ElementLeft == AbstractTag::GAS)
			{
				SwapPositions(sim, posX + 1, posY);
			}
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
