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

	float velX;
	float velY;

	Color color;
	Color colorPallette[4];

	//Properties of the element
	int temperature;
	int health;
	float density;
	float mass;
	float friction;
	

public:
	Element(int posX, int posY, int health = 100);
	Element();
	virtual ~Element();
	void SwapPositions(Simulation* sim, int swapX, int swapY);
	void UpdatePosition(int x, int y);
	bool CheckSurroundingElementsForAffect(Simulation* sim, int posX, int posY);


	virtual bool AffectOtherElement(Simulation* sim, int otherX, int otherY) = 0;
	virtual void UpdateElement(Simulation* sim) = 0;
	virtual bool SpecialBehavior(Simulation* sim) = 0;

	virtual void HeatUp(int amount);
	virtual void CoolDown(int amount);
	virtual void ReceiveDamage(int amount);

	int GetPosX();
	int GetPosY();
	const ElementTag& GetConcreteType();
	const AbstractTag& GetType();
	const Color& GetColor();
	const int GetDensity();

	//TODO: check if visitor pattern can help this
	ElementTag concreteTag;
	AbstractTag abstractTag;

	//ElementTag concreteTag;

	bool HasUpdated = false;
};

#endif // !ELEMENT_H


