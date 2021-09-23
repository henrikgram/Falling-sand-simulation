#include "Rock.h"

Rock::Rock(int posX, int posY) : ImmovableSolid(posX, posY), Solid(posX, posY), Element(posX, posY)
{
	tag = ElementTag::ROCK;
}

Rock::~Rock()
{
}
