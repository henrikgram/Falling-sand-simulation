#include "Element.h"

Element::Element(int posX, int posY)
{
	this->posX = posX;
	this->posY = posY;
}

Element::Element()
{
}

Element::~Element()
{
}

void Element::SwapPositions(Simulation* sim, Element* swapElement, int swapX, int swapY)
{

}

int Element::GetPosX()
{
	return posX;
}

int Element::GetPosY()
{
	return posY;
}

ElementTag Element::GetTag()
{
	return tag;
}
