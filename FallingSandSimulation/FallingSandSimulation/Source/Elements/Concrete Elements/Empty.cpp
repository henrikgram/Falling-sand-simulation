#include "Empty.h"

Empty::Empty(int posX, int posY) : Element(posX, posY)
{
	tag = ElementTag::EMPTY;
}

void Empty::UpdateElement(Simulation* sim)
{
}

Empty::Empty()
{
	tag = ElementTag::EMPTY;
}

Empty::~Empty()
{
}


