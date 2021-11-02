#pragma once
#include "../../Abstract elements/MovableSolid.h"
class Sand : public MovableSolid
{
public:
	Sand(int posX, int posY);
	virtual ~Sand();

	virtual bool SpecialBehavior(Simulation* sim) override;
	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
};

