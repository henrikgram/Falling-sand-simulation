#pragma once
#ifndef ELEMENT_H
#define ELEMENT_H

class Simulation;

#include "SFML/Graphics.hpp"
#include "../../Simulation.h"
#include "../../Enum/ElementTag.h"
using namespace sf;

class Element
{
protected:
	Vector2i position;
	Color color;
	ElementTag tag;

public:
	Element(Vector2i position );
	Element();
	virtual void UpdateElement(Simulation* sim) = 0;
	ElementTag GetTag();
};

#endif // !ELEMENT_H


