#include "Water.h"

Water::Water(int posX, int posY) : Liquid(posX, posY), Element(posX, posY)
{
	tag = ElementTag::WATER;
}

Water::~Water()
{
}
