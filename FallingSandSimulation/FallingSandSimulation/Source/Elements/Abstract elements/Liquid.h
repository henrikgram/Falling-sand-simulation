#pragma once
#include "Element.h"
class Liquid : virtual public Element
{
protected:
	int dispersionRate;
	int density;
public:
	Liquid(int posX, int posY, int dispersionRate = 1);
	bool IsValidMove(Simulation* sim, int dstX, int dstY) override;
	
	virtual ~Liquid();
	bool UpdateElement(Simulation* sim) override;
};

