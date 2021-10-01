#pragma once
#include "../../Abstract elements/Liquid.h"
class Acid : public Liquid
{
public:
	Acid(int posX, int posY, int dispersionRate = 4);
	~Acid();

	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
};

