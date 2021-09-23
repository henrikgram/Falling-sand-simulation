#pragma once
#include "..\Abstract elements\Gas.h"
class Smoke : public Gas
{
public:
	Smoke(int posX, int posY);
	virtual ~Smoke();
};

