#include "Rock.h"

Rock::Rock(int posX, int posY) : ImmovableSolid(posX, posY),  Element(posX, posY)
{
	concreteTag = ElementTag::ROCK;
	colorPallette[0] = Color(50, 50, 50);
	colorPallette[1] = Color(45, 45, 45);
	colorPallette[2] = Color(55, 55, 55);
	colorPallette[3] = Color(40, 40, 40);

	
	ignitionResistance = 50;
	maxTemperature = 1200;

	int colorPick = rand() % 4;
	color = colorPallette[colorPick];

}

Rock::~Rock()
{
}

bool Rock::SpecialBehavior(Simulation* sim)
{

	//coolsdown because of air
	CoolDown(1);

	return false;
}

bool Rock::Ignited(Simulation* sim)
{
	sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::LAVA, posX, posY));
	return true;
}

//void Rock::Ignite(Simulation* sim)
//{
//	if (temperature >= meltingPoint)
//	{
//		sim->ReplaceElement(sim->CreateElementFromTag(ElementTag::LAVA, posX, posY));
//	}
//}

bool Rock::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	return false;
}
