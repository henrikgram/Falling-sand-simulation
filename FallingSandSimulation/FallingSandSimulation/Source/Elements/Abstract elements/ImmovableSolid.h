#pragma once
#include "Element.h"
class ImmovableSolid : virtual public Element
{
public:
	ImmovableSolid(int posX, int posY);
	virtual ~ImmovableSolid();
	void UpdateElement(Simulation* sim) override;

};

