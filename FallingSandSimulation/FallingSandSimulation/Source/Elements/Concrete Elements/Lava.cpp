#include "Lava.h"

Lava::Lava(int posX, int posY, int dispersionRate) : Liquid(posX, posY, dispersionRate), Element(posX, posY)
{
	concreteTag = ElementTag::LAVA;

	colorPallette[0] = Color(255, 81, 13);
	colorPallette[1] = Color(255, 55, 0);
	colorPallette[2] = Color(255, 49, 13);
	colorPallette[3] = Color(255, 33, 13);

	int colorPick = rand() % 4;
	color = colorPallette[colorPick];
}

Lava::~Lava()
{
}

bool Lava::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	ElementTag element = sim->GetElementType(otherX,otherY);

	if (element == ElementTag::WATER)
	{
		CoolIntoRock(sim, otherX, otherY);
		return true;
	}
	else if (element == ElementTag::ROCK)
	{
		MeltIntoLava(sim, otherX, otherY);
	}
	
	return false;
}

void Lava::CoolIntoRock(Simulation* sim, int otherX, int otherY)
{
	//replace water with smoke
	sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::VAPOR, this->posX, this->posY));
	sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::ROCK, otherX, otherY));

}

void Lava::MeltIntoLava(Simulation* sim, int otherX, int otherY)
{
	//replace water with smoke
	sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::LAVA, otherX, otherY));
}
