#include "Element.h"

Element::Element(int posX, int posY, int health)
{
	this->posX = posX;
	this->posY = posY;
	this->health = health;
	temperature = 20;
	density = 1;
	health = 100;
	friction = 1;


	velocityX = 0;
	float randomVelX = rand() % 100;
	velocityY = randomVelX / 100;

	//TODO: this is not the best way
	terminalVelocity = density * 10;
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

	// y = ax + b to find slope
	float a;
	float b;

	int distance;
	bool positive = false;
	bool isStraightLine = false;

	//check if its the x distance or y distance the line has to follow
	float dstX =     (x - posX);
	float dstY =     (y - posY);

	if (dstX == 0 || dstY == 0)
	{
		isStraightLine = true;
	}

	bool isVertical = abs(dstX) < abs(dstY);// || dstY < 0;

	if (!isVertical)
	{
		distance = dstX;
	}
	else
	{
		distance = dstY;
	}

	if (!isStraightLine)
	{
		a = dstY / dstX;
		b = posY - a * posX;
	}
	
	
	//Problem here

	positive = distance < 0;
	distance = abs(distance);

	int originalX = posX;
	int originalY = posY;

	for (int i = 1; i <= distance; i++)
	{
		int newX = posX;
		int newY = posY;

		if (isVertical)
		{

			if (positive)
			{
				newY = originalY - i;
			}
			else
			{
				newY = i + originalY;
			}

			if (!isStraightLine)
			{
				//rearrange for x
				newX = floor((newY - b) / a);
			}
		}
		else
		{
			if (positive)
			{
				newX = originalX - i;

			}
			else
			{
				newX = i + originalX;
			}

			if (!isStraightLine)
			{
				newY = floor(newX * a + b);
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
	return true;
}

bool Element::IsValidMove(Simulation* sim, int dstX, int dstY)
{

	AbstractTag element = sim->GetAbstractType(dstX, dstY);


	if (element == AbstractTag::EMPTY)
	{
		return true;
	}
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

bool Element::hasChangedSinceLastFrame()
{
	if (prevX == posX && prevY == prevY)
	{
		return false;
	}
	else
	{
		return true;
	}
	
}

void Element::Die(Simulation* sim)
{
	sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::EMPTY, this->posX, this->posY));
}



void Element::AccelerateY(float gravity)
{
	if (velocityY < terminalVelocity)
	{
		velocityY += density * gravity;
	}

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

const float Element::GetFriction()
{
	return friction;
}
