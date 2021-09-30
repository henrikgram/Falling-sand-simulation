#include "Vapor.h"

Vapor::Vapor(int posX, int posY, int coolTime) : Gas(posX, posY), Element(posX, posY)
{
	this->coolTime = coolTime;

	concreteTag = ElementTag::VAPOR;

	colorPallette[0] = Color(180, 180, 180);
	colorPallette[1] = Color(185, 185, 185);
	colorPallette[2] = Color(190, 190, 190);
	colorPallette[3] = Color(195, 195, 195);

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
