#include "MovableSolid.h"
//#include <random>

MovableSolid::MovableSolid(int posX, int posY) : Element(posX, posY)
{
	abstractTag = AbstractTag::MOVABLESOLID;
}

MovableSolid::~MovableSolid()
{
}

void MovableSolid::UpdateElement(Simulation* sim)
{
	//TODO: have to find a solution to this 2 tag system
	//this adds 1k more microseconds from 7-8k woth brushsize 100;

	
	if (health <= 0)
	{
		sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::EMPTY, this->posX, this->posY));
		return;
	}


	if (IsValidMove(sim, posX, posY + 1))
	{
		MoveTo(sim, posX, posY + 1);
		AccelerateY(sim->GetGravity());
	}
	else
	{
		
		int direction =  rand() % 2 + 1;

		if (direction == 1)
		{
			if (IsValidMove(sim, posX - 1, posY + 1))
			{
				MoveTo(sim, posX - 1, posY + 1);
				return;
			}

		}
		else
		{
			if (IsValidMove(sim, posX + 1, posY + 1))
			{
				MoveTo(sim, posX + 1, posY + 1);
				return;
			}

		}

		if (velocityY >= 1)
		{

			if (direction == 1)
			{
				velocityX = velocityY;
			}
			else
			{
				velocityX = -velocityY;
			}
	
			velocityY = 0;
		}

		if (abs(floor(velocityX)) > 0)
		{
			if (velocityX > 0)
			{
				velocityX -= (friction /*+ sim->GetElement(posX, posY + 1)->GetFriction()*/);
			}
			else if (velocityX < 0)
			{
				velocityX += (friction /*+ sim->GetElement(posX, posY + 1)->GetFriction()*/);
			}
			else
			{
				velocityX = 0;
			}

			if (IsValidMove(sim, posX + floor(velocityX), posY))
			{
				MoveTo(sim, posX + floor(velocityX), posY);
			}
			
		}

		
	}
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


