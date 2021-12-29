#include "Snow.h"

Snow::Snow(int posX, int posY) : MovableSolid(posX, posY), Element(posX, posY)
{
	colorPallette[0] = Color(255, 255, 255);
	colorPallette[1] = Color(240, 255, 255);
	colorPallette[2] = Color(245, 255, 255);
	colorPallette[3] = Color(242, 255, 255);

	int colorPick = rand() % 4;

	concreteTag = ElementTag::SNOW;
	color = colorPallette[colorPick];

	freeFallResistance = 70;
	smoothness = 5;
	friction = 3;

	ignitionResistance = 60;
	maxTemperature = 5;
	temperature = -30;
}

Snow::~Snow()
{
}

bool Snow::UpdateElement(Simulation* sim)
{
	if (Element::UpdateElement(sim))
	{
		return true;
	}

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

	if (IsFreeFalling)
	{
		int direction = rand() % 2;

		if (direction == 1)
		{
			if (IsValidMove(sim, posX - 1, posY + 1))
			{
				MoveTo(sim, posX - 1, posY + 1);
				SetNeighbourToFreeFalling(sim);
				return true;
			}


		}
		else
		{
			if (IsValidMove(sim, posX + 1, posY + 1))
			{
				MoveTo(sim, posX + 1, posY + 1);
				SetNeighbourToFreeFalling(sim);
				return true;
			}


		}

	}


	if (IsValidMove(sim, posX, posY + 1))
	{
		MoveTo(sim, posX, posY + 1);
		SetNeighbourToFreeFalling(sim);
		IsFreeFalling = true;
		return true;
	}
	


	return false;
}

bool Snow::Ignited(Simulation* sim)
{
	sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::WATER, posX, posY));
	return true;
}

bool Snow::SpecialBehavior(Simulation* sim)
{
	if (rand() % 100 > 95)
	{
		HeatUp(sim, 1);
	}

	return false;
}

bool Snow::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	return false;
}
