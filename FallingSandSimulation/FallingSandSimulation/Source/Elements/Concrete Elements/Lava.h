#pragma once
#include "../Abstract elements/Liquid.h"
class Lava : public virtual Liquid
{
public:
	Lava(int posX, int posY, int dispersionRate = 2);
	virtual ~Lava();

	virtual bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
private:
	void CoolIntoRock(Simulation* sim, int otherX, int otherY);
	void MeltIntoLava(Simulation* sim, int otherX, int otherY);
};

