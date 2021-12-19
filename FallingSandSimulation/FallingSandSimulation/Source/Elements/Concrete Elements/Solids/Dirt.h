#pragma once
#include "../../Abstract elements/MovableSolid.h"
class Dirt : public MovableSolid
{
public:
	Dirt(int posX, int posY);
	virtual ~Dirt();


	virtual bool SpecialBehavior(Simulation* sim) override;
	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
};

