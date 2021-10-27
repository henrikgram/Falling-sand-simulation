#pragma once
#include "../../Abstract elements/ImmovableSolid.h"
class OutFlow : public ImmovableSolid
{
public:
	OutFlow(int posX, int posY);
	bool SpecialBehavior(Simulation* sim) override;
	virtual bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
	virtual ~OutFlow();
};

