#include "Empty.h"

Empty::Empty(Vector2i position) : Element(position)
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


