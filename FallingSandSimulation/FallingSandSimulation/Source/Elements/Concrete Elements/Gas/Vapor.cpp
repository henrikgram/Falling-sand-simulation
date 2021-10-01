#include "Vapor.h"

Vapor::Vapor(int posX, int posY, int coolTime) : Gas(posX, posY, health), Element(posX, posY)
{
	this->coolTime = coolTime;

	concreteTag = ElementTag::VAPOR;

	colorPallette[0] = Color(255, 255, 255);
	colorPallette[1] = Color(254, 254, 254);
	colorPallette[2] = Color(253, 253, 253);
	colorPallette[3] = Color(252, 252, 252);

	int colorPick = rand() % 4;
	color = colorPallette[colorPick];
}

bool Vapor::SpecialBehavior(Simulation* sim)
{
	coolTime--;

	if (coolTime <= 0)
	{
		sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::WATER, this->posX, this->posY));
		return true;
	}

	return false;
}

Vapor::~Vapor()
{
}
