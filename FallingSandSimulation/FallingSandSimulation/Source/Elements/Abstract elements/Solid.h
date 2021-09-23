#pragma once
#include "Element.h"
class Solid : virtual public Element
{
	//TODO: Find out about the need for virtual inheritance
public:
	Solid(int posX, int posY);
	virtual ~Solid();
};

