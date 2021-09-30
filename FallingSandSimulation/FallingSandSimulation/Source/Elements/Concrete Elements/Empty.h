#pragma once
#include "../Abstract elements/Element.h"
class Empty : public Element
{
public:
	Empty(int posX, int posY);
	void UpdateElement(Simulation* sim) override;
	virtual bool AffectOtherElement(Simulation* sim, int otherX, int otherY);
	bool SpecialBehavior(Simulation* sim) override;
	Empty();
	virtual ~Empty();

};

