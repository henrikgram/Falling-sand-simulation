#include "Element.h"

Element::Element(int posX, int posY, int health)
{
	this->posX = posX;
	this->posY = posY;
	this->health = health;
	temperature = 20;
	density = 1;
	health = 100;
}

Element::Element()
{
}

Element::~Element()
{
}

void Element::SwapPositions(Simulation* sim, int swapX, int swapY)
{
	Element* swapElement = sim->GetElement(swapX, swapY);

	swapElement->UpdatePosition(this->posX, this->posY);

	sim->SetElement(this->posX, this->posY, swapElement);
	sim->SetElement(swapX, swapY, this);

	this->UpdatePosition(swapX, swapY);
}

void Element::UpdatePosition(int x, int y)
{
	posX = x;
	posY = y;
}

bool Element::CheckSurroundingElementsForAffect(Simulation* sim, int posX, int posY)
{
	if (AffectOtherElement(sim, posX,posY + 1))
	{
		return true;
	}
	if (AffectOtherElement(sim, posX, posY - 1))
	{
		return true;
	}
	if (AffectOtherElement(sim, posX-1, posY))
	{
		 return true;
	}
	if (AffectOtherElement(sim, posX + 1, posY))
	{
		return true;
	}

	return false;

}

void Element::HeatUp(int heatAmount)
{
	temperature += heatAmount;
}

void Element::CoolDown(int amount)
{
	temperature -= amount;
}

void Element::ReceiveDamage(int amount)
{
	health -= amount;
}

int Element::GetPosX()
{
	return posX;
}

int Element::GetPosY()
{
	return posY;
}

const ElementTag& Element::GetConcreteType()
{
	return concreteTag;
}

const AbstractTag& Element::GetType()
{
	return abstractTag;
}

const Color& Element::GetColor()
{
	return color;
}

const int Element::GetDensity()
{
	return density;
}
