#include "Water.h"

Water::Water(int posX, int posY, int dispersionRate) : Liquid(posX, posY, dispersionRate), Element(posX, posY)
{
	concreteTag = ElementTag::WATER;

	colorPallette[0] = Color(0, 119, 255);
	colorPallette[1] = Color(0, 120, 255);
	colorPallette[2] = Color(0, 121, 255);
	colorPallette[3] = Color(0, 122, 255);

	int colorPick = rand() % 4;
	color = colorPallette[colorPick];
}

Water::~Water()
{
}
