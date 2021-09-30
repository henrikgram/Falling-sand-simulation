#pragma once
#include "Element.h"
class Liquid : virtual public Element
{
protected:
	int dispersionRate;
public:
	Liquid(int posX, int posY, int dispersionRate = 1);
	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
	virtual bool SpecialBehavior(Simulation* sim) override;
	virtual ~Liquid();
	void UpdateElement(Simulation* sim) override;
};

