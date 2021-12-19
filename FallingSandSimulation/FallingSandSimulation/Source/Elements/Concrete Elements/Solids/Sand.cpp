#include "Sand.h"

Sand::Sand(int posX, int posY) : MovableSolid(posX, posY), Element(posX, posY)
{
	colorPallette[0] = Color(240,216,0);
	colorPallette[1] = Color(250, 217, 0);
	colorPallette[2] = Color(224, 186, 0);
	colorPallette[3] = Color(250, 200, 0);
	
	int colorPick = rand() % 4;

	concreteTag = ElementTag::SAND;
	color = colorPallette[colorPick];

	freeFallResistance = 10;
	friction = 1;
	smoothness = 50;
}

Sand::~Sand()
{
}

bool Sand::SpecialBehavior(Simulation* sim)
{
	return false;
}

bool Sand::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	return false;
}
