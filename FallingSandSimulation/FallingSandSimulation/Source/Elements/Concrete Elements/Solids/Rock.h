#pragma once
#include "..\../Abstract elements\ImmovableSolid.h"
class Rock : public ImmovableSolid
{
public:
	Rock(int posX, int posY, int meltingPoint = 1200);
	virtual ~Rock();

	bool SpecialBehavior(Simulation* sim) override;

private:
	int meltingPoint;

};

