#pragma once
#include "..\..\Abstract elements\ImmovableSolid.h"
class Grass : public ImmovableSolid
{
public:
	Grass(int posX, int posY);
	virtual ~Grass();

	virtual bool SpecialBehavior(Simulation* sim) override;
	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
	//void Soak(Simulation* sim, int posX, int posY);

private:
	bool soaked;
};

