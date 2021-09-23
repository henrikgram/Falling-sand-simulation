#pragma once
#include "Solid.h"

class ImmovableSolid : virtual public Solid
{
public:
	ImmovableSolid(int posX, int posY);
	virtual ~ImmovableSolid();
	void UpdateElement(Simulation* sim) override;
};

