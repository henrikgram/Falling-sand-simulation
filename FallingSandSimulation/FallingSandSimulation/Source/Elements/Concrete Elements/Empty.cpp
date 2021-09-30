#include "Empty.h"

Empty::Empty(int posX, int posY) : Element(posX, posY)
{
	concreteTag = ElementTag::EMPTY;
	abstractTag = AbstractTag::EMPTY;
}

void Empty::UpdateElement(Simulation* sim)
{
}

bool Empty::AffectOtherElement(Simulation* sim, int otherX, int otherY)
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




