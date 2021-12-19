#include "ImmovableSolid.h"

ImmovableSolid::ImmovableSolid(int posX, int posY) :  Element(posX, posY)
{
	abstractTag = AbstractTag::IMMOVABLESOLID;
}

ImmovableSolid::~ImmovableSolid()
{
}

void ImmovableSolid::UpdateElement(Simulation* sim)
{
	if (health <= 0)
	{
		sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::EMPTY, this->posX, this->posY));
		return;
	}

	if (SpecialBehavior(sim))
	{
		return;
	}
}


