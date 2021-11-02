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

bool Element::MoveTo(Simulation* sim, int x, int y)
{
	//If its the same point, and the mouse haven't moved
	if (x == posX && y == posY)
	{
		//AddElementsInSquareArea(x1, y1, brushSize, element);
		return true;
	}

	// y = mx + b to find slope
	float lineBetweenPoints;
	int distance;
	bool positive = false;

	//check if its the x distance or y distance the line has to follow
	float dstX = (posX - x);
	float dstY = (posY - y);


	bool isVertical = abs(dstX) < abs(dstY) || dstY < 0;


	if (!isVertical)
	{
		distance = dstX;
		lineBetweenPoints = dstY / dstX;
	}
	else
	{
		distance = dstY;
		lineBetweenPoints = dstX / dstY;
	}

	positive = distance > 0;
	distance = abs(distance);

	int originalX = posX;
	int originalY = posY;

	for (int i = 1; i <= distance; i++)
	{
		int newX;
		int newY;

		if (isVertical)
		{
			if (positive)
			{
				newY = originalY - i;
				newX = round(i * lineBetweenPoints) + originalX;
			}
			else
			{
				newY = i + originalY;
				newX = round(i * lineBetweenPoints) + originalX;
			}
		}
		else
		{
			if (positive)
			{
				newX = i + originalX;
				newY = round(i * lineBetweenPoints) + originalY;
			}
			else
			{
				newX = originalX - i;
				newY = round(i * lineBetweenPoints) + originalY;
			}
		}

		if (IsValidMove(sim,newX,newY))
		{
			SwapPositions(sim, newX, newY);
		}
		else
		{
			return false;
		}
		//AddElementsInSquareArea(newX, newY, brushSize, element);
	}
	return false;
}

bool Element::IsValidMove(Simulation*, int dstX, int dstY)
{
	return false;
}

void Element::UpdateElement(Simulation* sim)
{
	if (SpecialBehavior(sim))
	{
		return;
	}

	if (isDead())
	{
		Die(sim);
	}

	if (CheckSurroundingElementsForAffect(sim, posX, posY))
	{
		return;
	}
	
}

//bool Element::Move(Simulation*, int dstX, int dstY)
//{
//	return false;
//}

bool Element::CheckSurroundingElementsForAffect(Simulation* sim, int posX, int posY)
{
	if (!sim->OutOfBounds(posX, posY + 1))
	{
		if (AffectOtherElement(sim, posX, posY + 1))
		{
			return true;
		}
	}
	if (!sim->OutOfBounds(posX, posY - 1))
	{
		if (AffectOtherElement(sim, posX, posY - 1))
		{
			return true;
		}
	}
	if (!sim->OutOfBounds(posX - 1, posY))
	{
		if (AffectOtherElement(sim, posX - 1, posY))
		{
			return true;
		}
	}
	if (!sim->OutOfBounds(posX + 1, posY))
	{
		if (AffectOtherElement(sim, posX + 1, posY))
		{
			return true;
		}
	}


	return false;

}

bool Element::isDead()
{
	if (health <= 0)
	{
		return true;
	}
	return false;
}

void Element::Die(Simulation* sim)
{
	sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::EMPTY, this->posX, this->posY));
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
