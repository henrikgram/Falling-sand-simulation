#pragma once
#include "..\..\Abstract elements\ImmovableSolid.h"
class InFlow : public ImmovableSolid
{
public:
	InFlow(int posX, int posY);
	~InFlow();

	bool SpecialBehavior(Simulation* sim) override;
	virtual bool AffectOtherElement(Simulation * sim, int otherX, int otherY) override;

private:
	ElementTag emitterType;

};

