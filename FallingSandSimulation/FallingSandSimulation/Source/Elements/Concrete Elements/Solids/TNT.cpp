#include "TNT.h"
#include "..\..\Abstract elements\Particle.h"
#include "..\Empty.h"

TNT::TNT(int posX, int posY) : MovableSolid(posX, posY), Element(posX, posY)
{
	colorPallette[0] = Color(255, 10, 0);
	colorPallette[1] = Color(255, 50, 0);
	colorPallette[2] = Color(255, 40, 0);
	colorPallette[3] = Color(255, 20, 0);

	int colorPick = rand() % 4;

	concreteTag = ElementTag::TNT;
	color = colorPallette[colorPick];

	freeFallResistance = 10;
	friction = 1;
	smoothness = 50;
	shouldExplode = false;
}

TNT::~TNT()
{
}

bool TNT::SpecialBehavior(Simulation* sim)
{
	if (shouldExplode)
	{
		Explode(sim, 3);
		return true;
	}
	return false;
}

bool TNT::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	AbstractTag at = sim->GetAbstractType(otherX, otherY);

	if (at != AbstractTag::EMPTY && at != AbstractTag::BOUNDS && at!= AbstractTag::PARTICLE)
	{
		Element* e = sim->GetElement(otherX, otherY);

		if (e->GetConcreteType() != concreteTag)
		{
			/*Particle* particle = new Particle(otherX, otherY, e->GetConcreteType(), e->GetColor(), 0, 2);
			sim->ReplaceElement(particle);
			Die(sim);*/

			Explode(sim, 3);
			return true;
		}
		
	}

	return false;
}

bool TNT::CheckSurroundingElementsForAffect(Simulation* sim, int posX, int posY)
{
	if (!sim->OutOfBounds(posX, posY + 1))
	{
		if (AffectOtherElement(sim, posX, posY + 1))
		{
			return true;
		}
	}
	/*if (!sim->OutOfBounds(posX, posY - 1))
	{
		if (AffectOtherElement(sim, posX, posY - 1))
		{
			return true;
		}
	}*/
	
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

void TNT::Explode(Simulation* sim, int radius)
{

	//TODO: this is reused code from simulation.cpp

	//Equation for circle
	//(x−a)^2+(y−b)^2=r^2
	float dstX;
	float dstY;
	float dstSquared;


	//Calculate the bounding box of the cicle
	int top = floor(posY - radius),
		bottom = ceil(posY + radius),
		left = floor(posX - radius),
		right = ceil(posX + radius);

	for (int yy = top; yy <= bottom; yy++) {
		for (int xx = left; xx <= right; xx++) {

			dstX = posX - xx;
			dstY = posY - yy;
			dstSquared = dstX * dstX + dstY * dstY;

			//if the distance to the point from the circles center is the radius or less, then it's inside the circle
			if (dstSquared <= radius * radius)
			{
				if (!sim->OutOfBounds(xx, yy))
				{
					Element* e = sim->GetElement(xx, yy);

					if (e->abstractTag != AbstractTag::EMPTY && e->abstractTag != AbstractTag::PARTICLE && e->GetConcreteType() != concreteTag)
					{
						//if (e->GetConcreteType() != ElementTag::SAND)
						//{
						//	this->velocityX = 5;
						//}
						//else if (e->GetConcreteType() == concreteTag)
						//{
						//	//TNT* t = dynamic_cast<TNT*>(e);
						//	//t->shouldExplode = true;
						//	//t->Explode(sim, 3);
						//	continue;
						//}
						Particle* particle = new Particle(xx, yy, e->GetConcreteType(), e->GetColor(), 1, -2);
						Empty* empty = new Empty(xx, yy);
						
						sim->ReplaceElement(particle);
					}
					

				}
			}
		}
	}


	Die(sim);
}

