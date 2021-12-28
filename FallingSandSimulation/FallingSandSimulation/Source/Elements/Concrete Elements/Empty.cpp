#include "Empty.h"

Empty::Empty(int posX, int posY) : Element(posX, posY)
{
	concreteTag = ElementTag::EMPTY;
	abstractTag = AbstractTag::EMPTY;
}

bool Empty::UpdateElement(Simulation* sim)
{
	return false;
}

bool Empty::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	return false;
}

bool Empty::SpecialBehavior(Simulation* sim)
{
	return false;
}

Empty::Empty()
{
	concreteTag = ElementTag::EMPTY;
}

Empty::~Empty()
{
}




