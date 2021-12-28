#pragma once
#include "Element.h"
class MovableSolid : virtual public Element
{
public: 
	MovableSolid(int posX, int posY);
	virtual ~MovableSolid();

	bool UpdateElement(Simulation* sim) override;
	bool IsValidMove(Simulation* sim, int dstX, int dstY) override;
	bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
	void SetFreeFall();

	void SetNeighbourToFreeFalling(Simulation* sim);


protected:
	float freeFallResistance;
	int smoothness;

private:
	bool IsFreeFalling;
	int stepCounter;
};

