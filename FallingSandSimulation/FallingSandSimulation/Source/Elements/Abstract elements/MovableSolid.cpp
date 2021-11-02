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
	//TODO: have to find a solution to this 2 tag system
	//this adds 1k more microseconds from 7-8k woth brushsize 100;
	//ElementTag ElementUnder = sim->GetElementType(posX, posY + 1);
	//AbstractTag ElementUnder2 = sim->GetAbstractType(posX, posY + 1);
	
	
	if (IsValidMove(sim, posX, posY + 1))
	{
		MoveTo(sim, posX, posY + 1);
	}
	else
	{
		int direction = rand() % 2 + 1;

		if (direction == 1)
		{
			if (IsValidMove(sim, posX - 1, posY + 1))
			{
				MoveTo(sim, posX - 1, posY + 1);
			}

		}
		else
		{
			if (IsValidMove(sim, posX + 1, posY + 1))
			{
				MoveTo(sim, posX + 1, posY + 1);
			}

			////ElementTag ElementLeft = sim->GetElementType(posX + 1, posY + 1);
			//AbstractTag ElementLeft2 = sim->GetAbstractType(posX + 1, posY + 1);
			//if (ElementLeft2 == AbstractTag::EMPTY || ElementLeft2 == AbstractTag::LIQUID)
			//{
			//	SwapPositions(sim, posX + 1, posY + 1);
			//}
		}
	}
}

bool MovableSolid::SpecialBehavior(Simulation* sim)
{
	return false;
}

bool MovableSolid::IsValidMove(Simulation* sim, int dstX, int dstY)
{
	AbstractTag element = sim->GetAbstractType(dstX, dstY);


	if (element == AbstractTag::EMPTY || element == AbstractTag::LIQUID)
	{
		return true;
	}
	return false;
}

bool MovableSolid::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	SwapPositions(sim, otherX, otherY);
	return false;
}
