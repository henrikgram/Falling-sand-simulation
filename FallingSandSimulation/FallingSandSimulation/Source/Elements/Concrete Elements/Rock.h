#pragma once
#include "..\Abstract elements\ImmovableSolid.h"
class Rock : public ImmovableSolid
{
public:
	Rock(int posX, int posY);
	virtual ~Rock();

};

