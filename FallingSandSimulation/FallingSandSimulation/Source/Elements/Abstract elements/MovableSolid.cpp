#include "MovableSolid.h"

MovableSolid::MovableSolid(int posX, int posY) : Solid(posX, posY), Element(posX, posY)
{
}

MovableSolid::~MovableSolid()
{
}

void MovableSolid::UpdateElement(Simulation* sim)
{
}
