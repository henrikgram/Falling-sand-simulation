#pragma once
#include "Element.h"
class Solid : virtual public Element
{
public:
	Solid(int posX, int posY);
	virtual ~Solid();
};

