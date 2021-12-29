#include "ImmovableSolid.h"

ImmovableSolid::ImmovableSolid(int posX, int posY) : Element(posX, posY)
{
	abstractTag = AbstractTag::IMMOVABLESOLID;
}

ImmovableSolid::~ImmovableSolid()
{
}

bool ImmovableSolid::UpdateElement(Simulation* sim)
{

	if (Element::UpdateElement(sim))
	{
		return true;
	}

	return true;
}




