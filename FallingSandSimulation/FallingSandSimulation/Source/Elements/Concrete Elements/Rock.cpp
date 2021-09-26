#include "Rock.h"

Rock::Rock(int posX, int posY) : ImmovableSolid(posX, posY), Solid(posX, posY), Element(posX, posY)
{
	tag = ElementTag::ROCK;
	colorPallette[0] = Color(50, 50, 50);
	colorPallette[1] = Color(45, 45, 45);
	colorPallette[2] = Color(55, 55, 55);
	colorPallette[3] = Color(40, 40, 40);

	int colorPick = rand() % 4;
	color = colorPallette[colorPick];

}

Rock::~Rock()
{
}
