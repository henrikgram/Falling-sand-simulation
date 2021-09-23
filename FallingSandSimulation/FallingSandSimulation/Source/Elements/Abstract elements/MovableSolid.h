#pragma once
#include "Solid.h"
class MovableSolid : virtual public Solid
{
public: 
	MovableSolid(int posX, int posY);
	virtual ~MovableSolid();

	void UpdateElement(Simulation* sim) override;
};

