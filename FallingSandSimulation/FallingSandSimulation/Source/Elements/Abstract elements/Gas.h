#pragma once
#include "Element.h"
class Gas : virtual public Element
{
public:
	Gas(int posX, int posY);
	virtual ~Gas();
	void UpdateElement(Simulation* sim) override;
	virtual bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
};

