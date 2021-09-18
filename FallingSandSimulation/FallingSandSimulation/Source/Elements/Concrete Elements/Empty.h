#pragma once
#include "../Abstract elements/Element.h"
class Empty : public Element
{
public:
	Empty(Vector2i position);
	void UpdateElement(Simulation* sim) override;
	Empty();

};

