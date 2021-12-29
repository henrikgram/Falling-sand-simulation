#pragma once
#include "..\..\Abstract elements\MovableSolid.h"
class Snow : public MovableSolid
{
public:
	Snow(int posX, int posY);
	virtual ~Snow();

	bool UpdateElement(Simulation* sim) override;
	bool Ignited(Simulation* sim) override;
	virtual bool SpecialBehavior(Simulation* sim) override;
	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;

};

