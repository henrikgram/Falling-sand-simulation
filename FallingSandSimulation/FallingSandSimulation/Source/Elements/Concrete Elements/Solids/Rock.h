#pragma once
#include "..\../Abstract elements\ImmovableSolid.h"
class Rock : public ImmovableSolid
{
public:
	Rock(int posX, int posY);
	virtual ~Rock();

	virtual bool SpecialBehavior(Simulation* sim) override;
	virtual void Ignite(Simulation* sim) override;
	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;

private:
	int meltingPoint;

};

