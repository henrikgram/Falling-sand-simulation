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
	ignitionResistance = 100;
	isIgnited = false;
	maxTemperature = 50;

	fireColors[0] = Color(242, 204, 12);
	fireColors[1] = Color(252, 186, 13);
	fireColors[2] = Color(230, 141, 0);
	fireColors[3] = Color(252, 127, 13);

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
	float dstX = (x - posX);
	float dstY = (y - posY);

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

		if (IsValidMove(sim, newX, newY))
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

	if (element == AbstractTag::EMPTY || element == AbstractTag::PARTICLE)
	{
		return true;
	}

	return false;
}


bool Element::UpdateElement(Simulation* sim)
{
	
	if (SpecialBehavior(sim))
	{
		return true;
	}

	if (isDead())
	{
		Die(sim);
		return true;
	}

	if (CheckSurroundingElementsForAffect(sim, posX, posY))
	{
		return true;
	}

	if (isIgnited)
	{

		if (Ignited(sim))
		{
			return true;
		}
	}

	return false;

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

void Element::HeatUp(Simulation* sim, int heatAmount)
{
	temperature += heatAmount;

	if (temperature > maxTemperature)
	{
		if (rand() % 100 > ignitionResistance)
		{
			Ignite(sim);
		}
	}


}

void Element::CoolDown(int amount)
{
	temperature -= amount;
}

void Element::ReceiveDamage(int amount)
{
	health -= amount;
}

void Element::Ignite(Simulation* sim)
{
	isIgnited = true;
}

bool Element::Ignited(Simulation* sim)
{
	int colorPick = rand() % 4;
	color = fireColors[colorPick];
	FireSpread(sim);

	//TODO: make it possible to put out fire
	//AbstractTag up = sim->GetAbstractType(posX, posY-1);
	//AbstractTag down = sim->GetAbstractType(posX, posY + 1);
	//AbstractTag left = sim->GetAbstractType(posX-1, posY);
	//AbstractTag right = sim->GetAbstractType(posX+1,posY);


	//ElementTag up2 = sim->GetElementType(posX, posY - 1);
	//ElementTag down2 = sim->GetElementType(posX, posY + 1);
	//ElementTag left2 = sim->GetElementType(posX - 1, posY);
	//ElementTag right2 = sim->GetElementType(posX + 1, posY);

	//if ( up == AbstractTag::LIQUID ||
	//	down == AbstractTag::LIQUID ||
	//	left == AbstractTag::LIQUID ||
	//	right == AbstractTag::LIQUID)
	//{
	//	isIgnited = false;
	//	temperature = 20;
	//	return false;
	//}

	if (rand() % 100 > 95)
	{
		if (sim->GetAbstractType(posX, posY - 1) == AbstractTag::EMPTY)
		{
			sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::SMOKE, posX, posY - 1));
		}
		else if (sim->GetAbstractType(posX + 1, posY - 1) == AbstractTag::EMPTY)
		{
			sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::SMOKE, posX + 1, posY - 1));
		}
		else if (sim->GetAbstractType(posX - 1, posY - 1) == AbstractTag::EMPTY)
		{
			sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::SMOKE, posX - 1, posY - 1));
		}
	}

	ReceiveDamage(rand() % 10);

	return false;
}

void Element::FireSpread(Simulation* sim)
{
	int heat = 100;

	switch (rand() % 4)
	{
	case(0):
		if (!sim->OutOfBounds(posX, posY + 1))
		{
			sim->GetElement(posX, posY + 1)->HeatUp(sim, rand() % heat);
		}
		break;
	case(1):
		if (!sim->OutOfBounds(posX, posY - 1))
		{
			sim->GetElement(posX, posY - 1)->HeatUp(sim, rand() % heat);

		}
		break;
	case(2):
		if (!sim->OutOfBounds(posX - 1, posY))
		{
			sim->GetElement(posX - 1, posY)->HeatUp(sim, rand() % heat);

		}
		break;
	case(3):
		if (!sim->OutOfBounds(posX + 1, posY))
		{
			sim->GetElement(posX + 1, posY)->HeatUp(sim, rand() % heat);

		}
		break;
	}





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
