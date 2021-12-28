#include "Particle.h"
#include <iostream>
Particle::Particle(int posX, int posY, ElementTag source, sf::Color sourceColor, int velX, int velY) : Element(posX,posY)
{
	this->source = source;


	this->velocityX = velX;
	this->velocityY = velY;
	this->color = sourceColor;
	this->abstractTag = AbstractTag::PARTICLE;
}

bool Particle::SpecialBehavior(Simulation* sim)
{
	return false;
}

void Particle::UpdateElement(Simulation* sim)
{
	AccelerateY(sim->GetGravity());

	if (IsValidMove(sim, posX + velocityX, posY + floor(velocityY)))
	{
		MoveTo(sim, posX + velocityX, posY + floor(velocityY));
	}
	else
	{
		if (sim->GetAbstractType(posX + velocityX, posY + floor(velocityY)) != AbstractTag::PARTICLE && sim->GetElementType(posX + velocityX, posY + floor(velocityY)) != ElementTag::TNT)
		{
			ReturnToElement(sim);
		}
	}

}

bool Particle::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{

	return false;
}


void Particle::ReturnToElement(Simulation* sim)
{
	sim->ReplaceElement(sim->CreateElementFromTag(source, posX, posY));
}

Particle::~Particle()
{
}
