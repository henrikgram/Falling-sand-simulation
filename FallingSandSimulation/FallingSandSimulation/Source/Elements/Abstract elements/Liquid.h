#pragma once
#include "Element.h"
class Liquid : virtual public Element
{
protected:
	int dispersionRate;
public:
	Liquid(int posX, int posY, int dispersionRate = 1);
	virtual ~Liquid();
	void UpdateElement(Simulation* sim) override;
};

