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

	int prevX;
	int prevY;

	Color color;
	Color colorPallette[4];
	Color fireColors[4];

	int temperature;
	int health;
	int density;
	int ignitionResistance;
	int maxTemperature;
	bool isIgnited;

	float terminalVelocity;
	float friction;

	float velocityX;
	float velocityY;



public:
	Element(int posX, int posY, int health = 100);
	Element();
	virtual ~Element();
	void SwapPositions(Simulation* sim, int swapX, int swapY);
	void UpdatePosition(int x, int y);
	bool MoveTo(Simulation* sim, int x, int y);
	virtual bool CheckSurroundingElementsForAffect(Simulation* sim, int posX, int posY);
	bool isDead();

	bool hasChangedSinceLastFrame();
	virtual void Die(Simulation* sim);

	virtual bool IsValidMove(Simulation*, int dstX, int dstY);
	virtual bool AffectOtherElement(Simulation* sim, int otherX, int otherY) = 0;
	virtual bool UpdateElement(Simulation* sim);
	virtual bool SpecialBehavior(Simulation* sim) = 0;

	void AccelerateY(float gravity);

	virtual void HeatUp(Simulation* sim, int amount);
	virtual void CoolDown(int amount);
	virtual void ReceiveDamage(int amount);
	virtual void Ignite(Simulation* sim);
	void FireSpread(Simulation* sim);
	


	int GetPosX();
	int GetPosY();
	const ElementTag& GetConcreteType();
	const AbstractTag& GetType();
	const Color& GetColor();
	const int GetDensity();
	const float GetFriction();

	//TODO: check if visitor pattern can help this
	ElementTag concreteTag;
	AbstractTag abstractTag;

	//ElementTag concreteTag;

	bool HasUpdated = false;
};

#endif // !ELEMENT_H


