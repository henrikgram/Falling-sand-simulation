#pragma once
#include "../../Abstract elements/Gas.h"
class Vapor : public virtual Gas
{
public:
	Vapor(int posX, int posY, int coolTime = 500);
	virtual bool SpecialBehavior(Simulation* sim) override;
	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
	virtual ~Vapor();

private:
	int coolTime;
	//int heat;
};

