#include "Acid.h"

Acid::Acid(int posX, int posY, int dispersionRate) : Liquid(posX, posY, dispersionRate), Element(posX, posY)
{
	concreteTag = ElementTag::ACID;

	colorPallette[0] = Color(64, 255, 100);
	colorPallette[1] = Color(60, 219, 86);
	colorPallette[2] = Color(55, 255, 100);
	colorPallette[3] = Color(61, 255, 100);

	int colorPick = rand() % 4;
	color = colorPallette[colorPick];
}

Acid::~Acid()
{
}

bool Acid::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	ElementTag element = sim->GetElementType(otherX, otherY);
	AbstractTag element2 = sim->GetAbstractType(otherX, otherY);

	if (element2 == AbstractTag::IMMOVABLESOLID || element2 == AbstractTag::MOVABLESOLID)
	{
		sim->GetElement(otherX, otherY)->ReceiveDamage(10);
		return true;
	}
	if (element == ElementTag::WATER || element == ElementTag::LAVA)
	{
		sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::SMOKE, this->posX, this->posY));
		return true;
	}

	return false;
}
