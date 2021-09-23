#pragma once
#ifndef ELEMENT_H
#define ELEMENT_H

class Simulation;

#include "SFML/Graphics.hpp"
#include "../../Simulation.h"
#include "../../Enum/ElementTag.h"
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
	virtual void UpdateElement(Simulation* sim) = 0;
	int GetPosX();
	int GetPosY();
	const ElementTag& GetTag();
	const Color& GetColor();
	ElementTag tag;

	bool HasUpdated = false;
};

#endif // !ELEMENT_H


