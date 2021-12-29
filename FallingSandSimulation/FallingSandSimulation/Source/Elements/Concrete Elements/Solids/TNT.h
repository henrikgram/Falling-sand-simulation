#pragma once
#include "..\..\Abstract elements\MovableSolid.h"
class TNT : public MovableSolid
{
public:

	TNT(int posX, int posY);
	bool shouldExplode;
	float strength;
	void Explode(Simulation* sim, int radius);
	virtual ~TNT();

	virtual bool SpecialBehavior(Simulation* sim) override;
	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
	virtual bool CheckSurroundingElementsForAffect(Simulation* sim, int posX, int posY) override;
	
};

