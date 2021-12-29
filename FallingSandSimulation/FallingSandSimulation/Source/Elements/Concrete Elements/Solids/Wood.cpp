#include "Wood.h"

Wood::Wood(int posX, int posY) : ImmovableSolid(posX, posY), Element(posX, posY)
{
	int alphaOffset = 200;
	colorPallette[0] = Color(82, 42, 16, 32 + alphaOffset);
	colorPallette[1] = Color(89, 40, 4, 35 + alphaOffset);
	colorPallette[2] = Color(77, 33, 0, 30 + alphaOffset);
	colorPallette[3] = Color(102, 51, 9, 40 + alphaOffset);

	int colorPick = rand() % 4;

	concreteTag = ElementTag::WOOD;
	color = colorPallette[colorPick];

	ignitionResistance = 30;
	maxTemperature = 200;
	health = 1500;

}

Wood::~Wood()
{
}

bool Wood::SpecialBehavior(Simulation* sim)
{
	return false;
}

bool Wood::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	return false;
}
