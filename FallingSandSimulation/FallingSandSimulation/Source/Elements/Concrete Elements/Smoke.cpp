#include "Smoke.h"

Smoke::Smoke(int posX, int posY) : Gas(posX, posY), Element(posX, posY)
{
	tag = ElementTag::SMOKE;

	colorPallette[0] = Color(180, 180, 180);
	colorPallette[1] = Color(185, 185, 185);
	colorPallette[2] = Color(190, 190, 190);
	colorPallette[3] = Color(195, 195, 195);

	int colorPick = rand() % 4;
	color = colorPallette[colorPick];
}

Smoke::~Smoke()
{
}
