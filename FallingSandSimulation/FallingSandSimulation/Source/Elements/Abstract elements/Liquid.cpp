#include "Liquid.h"

Liquid::Liquid(int posX, int posY, int dispersionRate) : Element(posX,posY)
{
	this->dispersionRate = dispersionRate;
	abstractTag = AbstractTag::LIQUID;
}

bool Liquid::AffectOtherElement(Simulation* sim, int otherX, int otherY)
{
	return false;
}

bool Liquid::SpecialBehavior(Simulation* sim)
{
	return false;
}

Liquid::~Liquid()
{
}

//TODO: add diagonal support.
void Liquid::UpdateElement(Simulation* sim)
{
	//TODO: this should work in the later checks
	if (CheckSurroundingElementsForAffect(sim, posX, posY))
	{
		return;
	}

	//if (AffectOtherElement(sim, posX,posY +1))
	//{
	//	return;
	//}

	//if (AffectOtherElement(sim, posX, posY - 1))
	//{
	//	return;
	//}

	//if under is empty go here first
	if (sim->GetAbstractType(posX, posY + 1) == AbstractTag::EMPTY)
	{
		SwapPositions(sim, posX, posY + 1);
	}
	else
	{
		int direction = rand() % 2 + 1;

		//Check all the way in the choosen direction, until it finds a not empty element

		//TODO maybe this is cursed
		if (dispersionRate > 1)
		{
			for (int i = 1; i <= dispersionRate; i++)
			{
				if (direction == 1)
				{

				
					//If it's at the end of the loop, and still hasn't found a filled element, then it just chooses this one.
					if (sim->GetAbstractType(posX - i, posY) == AbstractTag::EMPTY && i < dispersionRate)
					{
						continue;
					}
					else
					{
					/*	if (AffectOtherElement(sim, posX - (i - 1), posY))
						{
							return;
							break;
						}*/

						SwapPositions(sim, posX - (i - 1), posY);
						//SwapPositions(sim, posX - (i - 1), posY);

						break;
					}
				}
				else
				{
					if (sim->GetAbstractType(posX + i, posY) == AbstractTag::EMPTY && i < dispersionRate)
					{
						continue;
					}
					else
					{
						/*if (AffectOtherElement(sim, posX + (i - 1), posY))
						{
							return;
							break;
						}*/

						//SwapPositions(sim, posX + (i - 1), posY);
						SwapPositions(sim, posX + (i - 1), posY);
						break;
					}
				}
			}
		}
		else
		{
			if (direction == 1)
			{
				if (AffectOtherElement(sim, posX - 1, posY))
				{
					return;
				}

				if (sim->GetAbstractType(posX - 1, posY) == AbstractTag::EMPTY )
				{
					SwapPositions(sim, posX - 1, posY);
				}
			}
			else
			{
				if (AffectOtherElement(sim, posX + 1, posY))
				{
					return;
				}

				if (sim->GetAbstractType(posX + 1, posY) == AbstractTag::EMPTY )
				{
					
					SwapPositions(sim, posX + 1, posY);
				}
			}
		}
		

		
	}
}
