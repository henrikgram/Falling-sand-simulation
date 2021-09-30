#pragma once
#ifndef ELEMENT_H
#define ELEMENT_H

class Simulation;

#include "SFML/Graphics.hpp"
#include "../../Simulation.h"
#include "../../Enum/ElementTag.h"
#include "../../Enum/AbstractTag.h"
#include <random>
using namespace sf;

class Element
{
protected:
	int posX;
	int posY;
	Color color;
	Color colorPallette[4];
	

public:
	Element(int posX, int posY);
	Element();
	virtual ~Element();
	void SwapPositions(Simulation* sim, int swapX, int swapY);
	void UpdatePosition(int x, int y);
	virtual bool AffectOtherElement(Simulation* sim, int otherX, int otherY) = 0;
	virtual void UpdateElement(Simulation* sim) = 0;
	int GetPosX();
	int GetPosY();
	const ElementTag& GetConcreteType();
	const AbstractTag& GetType();
	const Color& GetColor();

	//TODO: check if visitor pattern can help this
	ElementTag concreteTag;
	AbstractTag abstractTag;

	//ElementTag concreteTag;

	bool HasUpdated = false;
};

#endif // !ELEMENT_H


