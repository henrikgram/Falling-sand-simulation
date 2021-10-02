#include "Simulation.h"

#include "Elements/Concrete Elements/Empty.h"
#include "Elements/Concrete Elements/Solids/Sand.h"
#include "Elements/Concrete Elements/Solids/Rock.h";
#include "Elements/Concrete Elements/Liquids/Water.h";
#include "Elements/Concrete Elements/Gas/Smoke.h"
#include "Elements/Concrete Elements/Liquids/Lava.h"
#include "Elements/Concrete Elements/Gas/Vapor.h"
#include "Elements/Concrete Elements/Liquids/Acid.h"

Simulation::Simulation(int width, int height)
{
	this->width = width;
	this->height = height;

	SimWorld = new std::vector<Element*>(width * height);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			SimWorld->at(Index(x, y)) = new Empty(x, y);
		}
	}
}

Simulation::~Simulation()
{
	int size = SimWorld->size();

	for (int i = size - 1; i >= 0; i--)
	{
		delete (*SimWorld)[i];
		(*SimWorld)[i] = nullptr;

	}

	delete SimWorld;
	SimWorld = nullptr;
}

void Simulation::UpdateSimulation()
{
	Elements = 0;

	int size = SimWorld->size();

	for (int i = size - 1; i >= 0; i--)
	{
		ElementTag concreteTag = (*SimWorld)[i]->GetConcreteType();
		if (concreteTag == ElementTag::EMPTY)
		{
			continue;
		}

		if (!(*SimWorld)[i]->HasUpdated)
		{
			(*SimWorld)[i]->HasUpdated = true;
			(*SimWorld)[i]->UpdateElement(this);
			Elements++;
		}
	}


	//Reset "has updated"
	for (int i = size - 1; i >= 0; i--)
	{
		if ((*SimWorld)[i]->GetConcreteType() == ElementTag::EMPTY)
		{
			continue;
		}

		(*SimWorld)[i]->HasUpdated = false;

	}
}

ElementTag Simulation::GetElementType(int x, int y)
{
	//TODO: this works but doesn't seem right
	if (OutOfBounds(x, y))
		//if(x > width && x > 0 && y < height && y >  0)
	{
		return ElementTag::BOUNDS;
	}

	else
	{
		return SimWorld->at(Index(x, y))->GetConcreteType();
	}

}


AbstractTag Simulation::GetAbstractType(int x, int y)
{
	//TODO: this works but doesn't seem right
	if (OutOfBounds(x, y))
		//if(x > width && x > 0 && y < height && y >  0)
	{
		return AbstractTag::BOUNDS;
	}

	else
	{
		return SimWorld->at(Index(x, y))->GetType();
	}
}

Element* Simulation::GetElement(int x, int y)
{
	return SimWorld->at(Index(x, y));
}

Element* Simulation::CreateElementFromTag(ElementTag concreteTag, int x, int y)
{
	switch (concreteTag)
	{
	case ElementTag::EMPTY:
		return new Empty(x, y);
		break;
	case ElementTag::SAND:
		return new Sand(x, y);
		break;
	case ElementTag::WATER:
		return new Water(x, y);
		break;
	case ElementTag::ROCK:
		return new Rock(x, y);
		break;
	case ElementTag::SMOKE:
		return new Smoke(x, y);
		break;
	case ElementTag::LAVA:
		return new Lava(x, y);
		break;
	case ElementTag::VAPOR:
		return new Vapor(x, y);
		break;
	case ElementTag::ACID:
		return new Acid(x, y);
		break;
	default:
		break;
	}
}

void Simulation::AddElementsBetweenPoints(int x1, int y1, int x2, int y2, ElementTag element, int brushSize)
{
	//If its the same point, and the mouse haven't moved
	if (x1 == x2 && y1 == y2)
	{
		for (int yy = 0; yy < brushSize; yy++)
		{
			for (int xx = 0; xx < brushSize; xx++)
			{
				if (!OutOfBounds(x1 + xx - brushSize / 2, y1 + yy - brushSize / 2))
				{
					ReplaceElement(CreateElementFromTag(element, x1 + xx - brushSize / 2, y1 + yy - brushSize / 2));
				}
				

			}

		}
		return;
	}

	// y = mx + b to find slope
	float lineBetweenPoints;
	int distance;
	bool positive = false;

	//check if its the x distance or y distance the line has to follow
	float dstX = (x2 - x1);
	float dstY = (y2 - y1);


	bool isVertical = abs(dstX) < abs(dstY);


	if (!isVertical)
	{
		distance = dstX;
		lineBetweenPoints = dstY / dstX;
	}
	else
	{
		distance = dstY;
		lineBetweenPoints = dstX / dstY;
	}

	positive = distance > 0;
	distance = abs(distance);

	for (int i = 0; i < distance; i++)
	{
		int newX;
		int newY;

		if (isVertical)
		{
		

			if (positive)
			{
				newY = i + y1;
				newX = round(i * lineBetweenPoints) + x1;
			}
			else
			{
				newY = i + y2;
				newX = round(i * lineBetweenPoints) + x2;
			}

			
		}
		else
		{
		

			if (positive)
			{
				newX = i + x1;
				newY = round(i * lineBetweenPoints) + y1;
			}
			else
			{
				newX = i + x2;
				newY = round(i * lineBetweenPoints) + y2;
			}

		}

		for (int yy = 0; yy < brushSize; yy++)
		{
			for (int xx = 0; xx < brushSize; xx++)
			{
				if (!OutOfBounds(newX + xx - brushSize / 2, newY + yy - brushSize / 2))
				{
					ReplaceElement(CreateElementFromTag(element, newX + xx - brushSize / 2, newY + yy - brushSize / 2));
				}
				

			}

		}

	}


}

void Simulation::SetElement(int x, int y, Element* element)
{
	//TOOD: check if this is deprecated
	SimWorld->at(Index(x, y)) = element;
}


void Simulation::ReplaceElement(Element* element)
{

	int x = element->GetPosX();
	int y = element->GetPosY();

	delete (SimWorld->at(Index(x, y)));
	(SimWorld->at(Index(x, y))) = nullptr;

	SimWorld->at(Index(x, y)) = element;
}

int Simulation::Index(int x, int y)
{
	return (y * width + x);
}

bool Simulation::OutOfBounds(int x, int y)
{
	if (Index(x, y) <= 0 || Index(x, y) >= (width) * (height))
	{
		return true;
	}
	else
	{
		return false;
	}
}






