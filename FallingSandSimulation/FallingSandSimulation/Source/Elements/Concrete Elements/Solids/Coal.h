#pragma once
#include "../../Abstract elements/MovableSolid.h"
class Coal : public MovableSolid
{
public:
	Coal(int posX, int posY);
	virtual ~Coal();


	virtual bool SpecialBehavior(Simulation* sim) override;
	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
};
