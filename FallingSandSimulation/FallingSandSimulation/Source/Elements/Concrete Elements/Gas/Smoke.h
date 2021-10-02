#pragma once
#include "..\..\Abstract elements\Gas.h"
class Smoke : public Gas
{
public:
	Smoke(int posX, int posY, int health = 100);
	virtual ~Smoke();
};

