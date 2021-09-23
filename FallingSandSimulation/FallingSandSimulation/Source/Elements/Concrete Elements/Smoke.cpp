#include "Smoke.h"

Smoke::Smoke(int posX, int posY) : Gas(posX, posY), Element(posX, posY)
{
	tag = ElementTag::SMOKE;
}

Smoke::~Smoke()
{
}
