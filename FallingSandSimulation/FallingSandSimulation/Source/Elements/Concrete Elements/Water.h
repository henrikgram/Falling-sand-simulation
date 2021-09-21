#pragma once
#include "../Abstract elements/Liquid.h"
class Water : public Liquid
{
public:
	Water(int posX, int posY);
	virtual ~Water();
};

