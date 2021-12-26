#include "Coal.h"

Coal::Coal(int posX, int posY) : MovableSolid(posX,posY), Element(posX,posY)
{
	int alphaOffset = 150;
	colorPallette[0] = Color(46, 51, 50, 20 + alphaOffset);
	colorPallette[1] = Color(34, 38, 4, 15 + alphaOffset);
	colorPallette[2] = Color(20, 20, 0, 8 + alphaOffset);
	colorPallette[3] = Color(25, 28, 9, 11 + alphaOffset);

	int colorPick = rand() % 4;

	concreteTag = ElementTag::COAL;
	color = colorPallette[colorPick];

	freeFallResistance = 80;
	smoothness = 3;
	friction = 5;
}

Coal::~Coal()
{
}

bool Coal::SpecialBehavior(Simulation* sim)
{
    return false;
}

bool Coal::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
    return false;
}
