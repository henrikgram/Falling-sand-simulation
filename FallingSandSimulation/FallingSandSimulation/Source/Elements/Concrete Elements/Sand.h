#pragma once
#include "../Abstract elements/MovableSolid.h"
class Sand : public MovableSolid
{
public:
	Sand(int posX, int posY);
	Sand();
	virtual ~Sand();
};

