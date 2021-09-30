#pragma once
#include "Solid.h"

class ImmovableSolid : virtual public Solid
{
public:
	ImmovableSolid(int posX, int posY);
	virtual ~ImmovableSolid();
	void UpdateElement(Simulation* sim) override;
	virtual bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
};

