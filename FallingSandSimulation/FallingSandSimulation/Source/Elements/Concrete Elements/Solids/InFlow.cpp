#include "InFlow.h"

InFlow::InFlow(int posX, int posY) : ImmovableSolid(posX, posY), Solid(posX, posY), Element(posX, posY)
{
	concreteTag = ElementTag::INFLOW;
	emitterType = ElementTag::EMPTY;
	color = Color::Cyan;
}

InFlow::~InFlow()
{
}

bool InFlow::SpecialBehavior(Simulation* sim)
{
	if (emitterType == ElementTag::EMPTY)
	{
		Element::CheckSurroundingElementsForAffect(sim, posX, posY);
	}
	else
	{
		if (!sim->OutOfBounds(posX, posY + 1))
		{
			ElementTag element = sim->GetElementType(posX, posY + 1);

			if (element == ElementTag::EMPTY)
			{
				sim->ReplaceElement(sim->CreateElementFromTag(emitterType, posX, posY + 1));

			}
			return true;
		}


		/*for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (x == 0 && y == 0)
				{
					continue;
				}
				else
				{
					ElementTag element = sim->GetElementType(posX + x, posY + y);

					if (element == ElementTag::EMPTY)
					{
						sim->ReplaceElement(sim->CreateElementFromTag(emitterType, posX + x, posY + y));

					}
				}
			}
		}
		return true;*/
	}
	return false;
}

bool InFlow::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	ElementTag element = sim->GetElementType(otherX, otherY);
	if (element != ElementTag::EMPTY && element != ElementTag::INFLOW && element != ElementTag::OUTFLOW)
	{
		emitterType = element;
		return true;
	}
	return false;
}
