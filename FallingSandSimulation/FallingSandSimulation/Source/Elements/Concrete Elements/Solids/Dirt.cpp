#include "Dirt.h"

Dirt::Dirt(int posX, int posY) : MovableSolid(posX, posY), Element(posX, posY)
{
	int alphaOffset = 150;
	colorPallette[0] = Color(82, 42, 16, 32 + alphaOffset);
	colorPallette[1] = Color(89, 40, 4, 35 + alphaOffset);
	colorPallette[2] = Color(77, 33, 0, 30 + alphaOffset);
	colorPallette[3] = Color(102, 51, 9, 40 + alphaOffset);

	int colorPick = rand() % 4;

	concreteTag = ElementTag::DIRT;
	color = colorPallette[colorPick];

	freeFallResistance = 70;
	smoothness = 5;
	friction = 3;
}

Dirt::~Dirt()
{
}

bool Dirt::SpecialBehavior(Simulation* sim)
{
	return false;
}

bool Dirt::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	if (sim->GetElementType(otherX, otherY) == ElementTag::WATER)
	{
		if (rand() % 100 > 90)
		{
			sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::GRASS, posX, posY));
			sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::EMPTY, otherX, otherY));
			return true;
		}
	}
	return false;
}





