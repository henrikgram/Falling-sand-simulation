#pragma once
#include "Element.h"
class Gas : virtual public Element
{
public:
	Gas(int posX, int posY, int health);
	virtual ~Gas();
	void UpdateElement(Simulation* sim) override;
	virtual bool IsValidMove(Simulation* sim, int dstX, int dstY) override;
};

