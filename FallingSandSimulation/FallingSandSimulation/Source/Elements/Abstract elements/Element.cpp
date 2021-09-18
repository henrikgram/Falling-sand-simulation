#include "Element.h"

Element::Element(Vector2i position)
{
	this->position = position;
	this->color = color;
}

Element::Element()
{
}

ElementTag Element::GetTag()
{
	return tag;
}
