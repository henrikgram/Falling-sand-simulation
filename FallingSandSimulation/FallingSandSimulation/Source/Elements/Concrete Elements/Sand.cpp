#include "Sand.h"

Sand::Sand(int posX, int posY) : MovableSolid(posX, posY), Solid(posX, posY), Element(posX, posY)
{
	tag = ElementTag::SAND;
}

Sand::~Sand()
{
}
