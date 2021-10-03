#include "MovableSolid.h"
//#include <random>

MovableSolid::MovableSolid(int posX, int posY) : Solid(posX, posY), Element(posX, posY)
{
	abstractTag == AbstractTag::MOVABLESOLID;
}

MovableSolid::~MovableSolid()
{
}

void MovableSolid::UpdateElement(Simulation* sim)
{

	int under = floor(velY) + posY;
	AbstractTag ElementUnder2 = sim->GetAbstractType(posX, posY +1);


	if (ElementUnder2 == AbstractTag::EMPTY || ElementUnder2 == AbstractTag::LIQUID)
	{
		//rounds velocity down;
		SwapPositions(sim, posX, posY + 1);
		velY += 0.01f;
		return;
	
	}

	int direction = rand() % 2 + 1;
	
	if (velY > 0)
	{
		if (direction == 1)
		{
			velX = velY;
		}
		else
		{
			velX = -velY;
		}
		
		velY = 0;
	}


	if (abs(velX) > 0)
	{
		if (velX > 0)
		{
			velX -= friction;
		}
		else if (velX < 0)
		{
			velX += friction;
		}
		else
		{
			velX = 0;
		}

		AbstractTag ElementRight2 = sim->GetAbstractType(posX + round(velX), posY);

		if (ElementRight2 == AbstractTag::EMPTY || ElementRight2 == AbstractTag::LIQUID)
		{
			SwapPositions(sim, posX + round(velX), posY);
		}
	}

	if (direction == 1)
	{
		//ElementTag ElementRight = sim->GetElementType(posX - 1, posY + 1);
		AbstractTag ElementRight2 = sim->GetAbstractType(posX - 1, posY + 1);

		if (ElementRight2 == AbstractTag::EMPTY || ElementRight2 == AbstractTag::LIQUID)
		{
			SwapPositions(sim, posX - 1, posY + 1);
			return;
		}
	}
	else
	{

		//ElementTag ElementLeft = sim->GetElementType(posX + 1, posY + 1);
		AbstractTag ElementLeft2 = sim->GetAbstractType(posX + 1, posY + 1);
		if (ElementLeft2 == AbstractTag::EMPTY || ElementLeft2 == AbstractTag::LIQUID)
		{
			SwapPositions(sim, posX + 1, posY + 1);
			return;
		}
	}




}

bool MovableSolid::SpecialBehavior(Simulation* sim)
{
	return false;
}

bool MovableSolid::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	return false;
}
