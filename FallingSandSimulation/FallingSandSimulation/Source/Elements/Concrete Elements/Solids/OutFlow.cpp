#include "OutFlow.h"

OutFlow::OutFlow(int posX, int posY) : ImmovableSolid(posX, posY), Solid(posX, posY), Element(posX, posY)
{
	color = Color::Magenta;
	concreteTag = ElementTag::OUTFLOW;
}

bool OutFlow::SpecialBehavior(Simulation* sim)
{
	AffectOtherElement(sim, posX, posY + 1);
	AffectOtherElement(sim, posX, posY - 1);
	AffectOtherElement(sim, posX - 1, posY);
	AffectOtherElement(sim, posX + 1, posY);

	return true;

}

bool OutFlow::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	if (!sim->OutOfBounds(otherX, otherY))
	{
		ElementTag element = sim->GetElementType(otherX, otherY);
		if (element != ElementTag::EMPTY && element != ElementTag::OUTFLOW)
		{
			sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::EMPTY, otherX, otherY));
			return true;
		}

	}

	return false;
}

OutFlow::~OutFlow()
{
}
