#pragma once
#include "Element.h"
class ImmovableSolid : virtual public Element
{
public:
	ImmovableSolid(int posX, int posY);
	virtual ~ImmovableSolid();
	bool UpdateElement(Simulation* sim) override;

};

