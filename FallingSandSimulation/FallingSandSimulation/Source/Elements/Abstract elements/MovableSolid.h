#pragma once
#include "Solid.h"
class MovableSolid : virtual public Solid
{
public: 
	MovableSolid(Vector2i position);

	void UpdateElement(Simulation* sim) override;
};

