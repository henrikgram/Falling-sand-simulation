#pragma once
#include "Element.h"
class Particle : public Element
{
private:
	ElementTag source;

public:
	Particle(int posX, int posY, ElementTag source, sf::Color sourceColor, int velX, int velY);
	virtual bool SpecialBehavior(Simulation* sim) override;
	virtual bool UpdateElement(Simulation* sim) override;
	virtual bool AffectOtherElement(Simulation* sim, int otherX, int otherY) override;
	
	void ReturnToElement(Simulation* sim);
	~Particle();

};

