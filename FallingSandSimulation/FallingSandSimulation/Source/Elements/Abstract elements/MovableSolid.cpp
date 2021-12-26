#include "MovableSolid.h"
//#include <random>

MovableSolid::MovableSolid(int posX, int posY) : Element(posX, posY)
{
	abstractTag = AbstractTag::MOVABLESOLID;

	stepCounter = 0;
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

	//TODO: implement true velocity
	if (!hasChangedSinceLastFrame())
	{
		if (stepCounter >= smoothness)
		{
			IsFreeFalling = false;
		}
		else
		{
			stepCounter++;
		}

	}
	else
	{

		stepCounter = 0;
	}

	prevX = posX;
	prevY = posY;

	if (IsValidMove(sim, posX, posY + 1))
	{
		MoveTo(sim, posX, posY + 1);
		AccelerateY(sim->GetGravity());
		IsFreeFalling = true;
		SetNeighbourToFreeFalling(sim);
	}
	else if (IsFreeFalling)
	{
		int direction = rand() % 2;

		if (direction == 1)
		{
			if (IsValidMove(sim, posX - 1, posY + 1))
			{
				MoveTo(sim, posX - 1, posY + 1);
				SetNeighbourToFreeFalling(sim);
				return;
			}
	

		}
		else
		{
			if (IsValidMove(sim, posX + 1, posY + 1))
			{
				MoveTo(sim, posX + 1, posY + 1);
				SetNeighbourToFreeFalling(sim);
				return;
			}


		}


		if (velocityY >= 1)
		{

			if (direction == 1)
			{
				velocityX = velocityY - (freeFallResistance / 100);
			}
			else
			{
				velocityX = -velocityY + (freeFallResistance / 100);
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
				SetNeighbourToFreeFalling(sim);
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

bool MovableSolid::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	AbstractTag other = sim->GetAbstractType(otherX, otherY);

	if (other == AbstractTag::MOVABLESOLID)
	{
		MovableSolid* m = dynamic_cast<MovableSolid*>(sim->GetElement(otherX, otherY));
		if (!m->IsFreeFalling)
		{
			m->SetFreeFall();
			return true;
		}

	}
	return false;
}

void MovableSolid::SetFreeFall()
{
	float chance = rand() % 100;
	if (chance > freeFallResistance)
	{
		IsFreeFalling = true;
		stepCounter = 0;
	}

}

void MovableSolid::SetNeighbourToFreeFalling(Simulation* sim)
{

	MovableSolid* m;

	if (!sim->OutOfBounds(posX, posY + 1))
	{

		MovableSolid* m = dynamic_cast<MovableSolid*>(sim->GetElement(posX, posY + 1));

		if (m != nullptr)
		{
			m->SetFreeFall();
		}

	}

	if (!sim->OutOfBounds(posX - 1, posY))
	{
		MovableSolid* m = dynamic_cast<MovableSolid*>(sim->GetElement(posX - 1, posY));

		if (m != nullptr)
		{
			m->SetFreeFall();
		}
	}
	if (!sim->OutOfBounds(posX + 1, posY))
	{
		MovableSolid* m = dynamic_cast<MovableSolid*>(sim->GetElement(posX + 1, posY));

		if (m != nullptr)
		{
			m->SetFreeFall();
		}
	}


}


