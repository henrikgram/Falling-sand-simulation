#include "Simulation.h"
#include "Elements/Concrete Elements/Empty.h"
#include "Elements/Concrete Elements/Sand.h"

Simulation::Simulation(int width, int height)
{
	this->width = width;
	this->height = height;

	SimWorld = new std::vector<Element*>(width * height);
	SimWorld2 = new Empty[width * height];
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


	//for (auto i: *SimWorld)
	//{
	//	/*if (i->GetTag() == ElementTag::EMPTY)
	//	{
	//		continue;
	//	}
	//	i->UpdateElement(this);*/
	//}

	int size = SimWorld->size();

	for (int i = size-1; i >= 0; i--)
	{
		if ((*SimWorld)[i]->GetTag() == ElementTag::EMPTY)
		{
			continue;
		}
		(*SimWorld)[i]->UpdateElement(this);
	}
	
	
}

ElementTag Simulation::GetElementTag(int x, int y)
{
	if (Index(x,y) < 0 || Index(x, y) > width*height)
	{
		return ElementTag::BOUNDS;
	}
	else if (x < 0 || x > width)
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






