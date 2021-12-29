#pragma once
#include "..\..\Abstract elements\ImmovableSolid.h"
class Wood : public ImmovableSolid
{
public:
	Wood(int posX, int posY);
	virtual ~Wood();

	virtual bool SpecialBehavior(Simulation* sim) override;
	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;


};

