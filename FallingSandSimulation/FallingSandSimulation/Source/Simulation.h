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
	Element* SimWorld2;
	std::stack<Element*>* ElementsToDelete;


public:
	Simulation(int width, int height);
	void UpdateSimulation();
	ElementTag GetElementTag(int x, int y);
	Element* GetElement(int x, int y);
	void SetElement(int x, int y, Element* element);
	void ReplaceElement(Element* element);
	int Index(int x, int y);

	int Elements = 0;




};

#endif // !SIMULATION_H

