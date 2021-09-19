#pragma once
#ifndef SIMULATION_H
#define SIMUALTION_H
class Element;
#include "Elements/Abstract elements/Element.h"
#include "Enum/ElementTag.h"
#include <vector>
#include <stack>

class Simulation
{
private:
	int width;
	int height;
	std::vector<Element*>* SimWorld;
	std::stack<Element*>* ElementsToDelete;

public:
	Simulation(int width, int height);
	ElementTag GetElementTag(int x, int y);
	void SetElement(Element* element);
	void DeleteElements();



};

#endif // !SIMULATION_H

