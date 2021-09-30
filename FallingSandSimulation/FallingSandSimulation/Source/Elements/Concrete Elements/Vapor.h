#pragma once
#include "../Abstract elements/Gas.h"
class Vapor : public virtual Gas
{
public:
	Vapor(int posX, int posY, int coolTime = 500);
	bool SpecialBehavior(Simulation* sim) override;
	virtual ~Vapor();

private:
	int coolTime;
	//int heat;
};

