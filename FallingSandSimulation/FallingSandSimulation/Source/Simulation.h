#pragma once
#ifndef SIMULATION_H
#define SIMUALTION_H
class Element;
#include "Elements/Abstract elements/Element.h"
#include "Enum/ElementTag.h"
#include <vector>

class Simulation
{
private:
	
public:
	Simulation(int width, int height);
	ElementTag GetElementTag(int x, int y);
	void SetElement(Element* element, int y, int x);

	int width;
	int height;
	std::vector<Element*>* SimWorld;
};

#endif // !SIMULATION_H

