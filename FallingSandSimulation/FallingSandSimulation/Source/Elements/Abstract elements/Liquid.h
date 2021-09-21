#pragma once
#include "Element.h"
class Liquid : virtual public Element
{
public:
	Liquid(int posX, int posY);
	virtual ~Liquid();
	void UpdateElement(Simulation* sim) override;
};

