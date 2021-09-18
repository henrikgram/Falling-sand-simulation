#include "MovableSolid.h"

MovableSolid::MovableSolid(Vector2i position) : Solid(position), Element(position)
{
}

void MovableSolid::UpdateElement(Simulation* sim)
{
}
