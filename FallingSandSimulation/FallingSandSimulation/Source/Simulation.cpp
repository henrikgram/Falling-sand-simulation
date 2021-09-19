#include "Simulation.h"
#include "Elements/Concrete Elements/Empty.h"
#include "Elements/Concrete Elements/Sand.h"

Simulation::Simulation(int width, int height)
{
	this->width = width;
	this->height = height;

	SimWorld = new std::vector<Element*>(width * height);
	ElementsToDelete = new std::stack<Element*>;
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			SimWorld->at(Index(x,y)) = new Empty(x,y);
		}
	}
}

void Simulation::UpdateSimulation()
{
	std::vector<Element*>::iterator it;
	int i = 0;
	for (it = SimWorld->begin(); it < SimWorld->end(); it++)
	{
		i++;
		if ((*it)->GetTag() == ElementTag::EMPTY)
		{
			continue;
		}

		//(*it)->UpdateElement(this);
	}
	
}

ElementTag Simulation::GetElementTag(int x, int y)
{
	if (Index(x,y) < 0 || Index(x, y) > width*height)
	{
		return ElementTag::BOUNDS;
	}
	else
	{
		return SimWorld->at(Index(x, y))->GetTag();
	}
	
}

Element* Simulation::GetElement(int x, int y)
{
	return SimWorld->at(Index(x, y));
}

void Simulation::SetElement(int x, int y, Element* element)
{
	
	SimWorld->at(Index(x, y)) = element;
}


void Simulation::ReplaceElement(Element* element)
{
	//TODO: memory leak
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






