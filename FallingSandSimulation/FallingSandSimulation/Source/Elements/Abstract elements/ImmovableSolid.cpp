#include "ImmovableSolid.h"

ImmovableSolid::ImmovableSolid(int posX, int posY) : Solid(posX, posY), Element(posX, posY)
{
}

ImmovableSolid::~ImmovableSolid()
{
}

void ImmovableSolid::UpdateElement(Simulation* sim)
{
}
