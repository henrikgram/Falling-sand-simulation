#include "Grass.h"

Grass::Grass(int posX, int posY) : ImmovableSolid(posX, posY), Element(posX, posY)
{
	concreteTag = ElementTag::GRASS;

	colorPallette[0] = Color(218, 245, 137);
	colorPallette[1] = Color(188, 252, 119);
	colorPallette[2] = Color(152, 230, 120);
	colorPallette[3] = Color(125, 252, 119);


	ignitionResistance = 20;
	maxTemperature = 100;

	int colorPick = rand() % 4;
	color = colorPallette[colorPick];
	soaked = false;
}

Grass::~Grass()
{
}

bool Grass::SpecialBehavior(Simulation* sim)
{
	return false;
}

bool Grass::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	
		if (sim->GetElementType(otherX,otherY) == ElementTag::WATER)
		{
			if (!soaked)
			{
				soaked = true;
				color = sf::Color(color.r, color.g, color.b, 150);
				sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::EMPTY, otherX, otherY));
				return true;
			}
			else
			{
				if (rand() % 100 > 90)
				{
					if (sim->GetElementType(posX, posY+1) == ElementTag::GRASS)
					{
						Element* e = sim->GetElement(posX, posY + 1);
						Grass* g = dynamic_cast<Grass*>(e);

						if (!g->soaked)
						{
						
							g->soaked = true;
							g->color = sf::Color(color.r, color.g, color.b, 150);
							sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::EMPTY, otherX, otherY));
							return true;
						}
					}
				}
			}
			
		}
	


	return false;
}


