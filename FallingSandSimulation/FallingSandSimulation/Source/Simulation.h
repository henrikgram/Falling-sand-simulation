#pragma once
#ifndef SIMULATION_H
#define SIMUALTION_H
class Element;
#include "Elements/Abstract elements/Element.h"
#include "Enum/ElementTag.h"
#include "Enum/AbstractTag.h"
#include <vector>
#include <stack>
#include <thread>

class Simulation
{
private:
	int width;
	int height;
	std::vector<Element*>* SimWorld;
	bool UpdateFromLeft = false;
	std::vector<std::thread> workers;
	
public:
	Simulation(int width, int height);
	~Simulation();

	void UpdateSimulation(int updateStart, int updateEnd);
	void Update();
	void ResetSimulation();

	Element* CreateElementFromTag(ElementTag concreteTag, int x, int y);
	void AddElementsInSquareArea(int x, int y, int brushSize, ElementTag element);
	void AddElementsInCircleArea(int x, int y, int brushSize, ElementTag element);

	void AddElementsBetweenPoints(int x1, int y1, int x2, int y2,ElementTag element, int brushSize);
	void SaveSimState(const char* fileName);
	
	void SetElement(int x, int y, Element* element);
	void ReplaceElement(Element* element);
	int Index(int x, int y);
	bool OutOfBounds(int x, int y);
	int Elements = 0;

	//GET
	ElementTag GetElementType(int x, int y);
	AbstractTag GetAbstractType(int x, int y);
	Element* GetElement(int x, int y);
	float GetGravity();
	//Config
private:
	float gravity;







};

#endif // !SIMULATION_H

