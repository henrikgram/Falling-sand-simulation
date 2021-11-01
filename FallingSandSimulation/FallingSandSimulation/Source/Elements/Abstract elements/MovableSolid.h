#pragma once
#include "Solid.h"
class MovableSolid : virtual public Solid
{
public: 
	MovableSolid(int posX, int posY);
	virtual ~MovableSolid();

	void UpdateElement(Simulation* sim) override;
	virtual bool SpecialBehavior(Simulation* sim) override;
	bool IsValidMove(Simulation* sim, int dstX, int dstY) override;
	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
};

