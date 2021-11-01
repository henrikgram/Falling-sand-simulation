#pragma once
#ifndef SIMULATION_H
#define SIMUALTION_H
class Element;
#include "Elements/Abstract elements/Element.h"
#include "Enum/ElementTag.h"
#include "Enum/AbstractTag.h"
#include <vector>
#include <stack>

class Simulation
{
private:
	int width;
	int height;
	std::vector<Element*>* SimWorld;
	std::stack<Element*>* elementsTobeDeleted;

public:
	Simulation(int width, int height);
	~Simulation();

	void UpdateSimulation();
	ElementTag GetElementType(int x, int y);
	AbstractTag GetAbstractType(int x, int y);
	Element* GetElement(int x, int y);
	Element* CreateElementFromTag(ElementTag concreteTag, int x, int y);
	void AddElementsInSquareArea(int x, int y, int brushSize, ElementTag element);
	void AddElementsInCircleArea(int x, int y, int brushSize, ElementTag element);

	void AddElementsBetweenPoints(int x1, int y1, int x2, int y2,ElementTag element, int brushSize);
	
	void SetElement(int x, int y, Element* element);
	void ReplaceElement(Element* element);
	int Index(int x, int y);
	bool OutOfBounds(int x, int y);
	int Elements = 0;




	template<typename T, typename F>
	void AddElementsBetweenPoints(int x1, int y1, int x2, int y2, ElementTag element, int brushSize, T&& t, F&& f);

};

#endif // !SIMULATION_H

