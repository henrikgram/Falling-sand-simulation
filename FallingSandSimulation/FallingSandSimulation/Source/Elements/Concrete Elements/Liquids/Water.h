#pragma once
#include "../../Abstract elements/Liquid.h"
class Water : public Liquid
{
public:
	Water(int posX, int posY, int dispersionRate = 5);
	virtual ~Water();
};

