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
			SimWorld->at(y * width + x) = new Empty(x,y);
		}
	}
}

ElementTag Simulation::GetElementTag(int x, int y)
{
	return SimWorld->at(y * width + x)->GetTag();
}

void Simulation::SetElement(Element* element)
{
	//TODO: memory leak
	int x = element->GetPosX();
	int y = element->GetPosY();

	delete (SimWorld->at(y * width + x));
	(SimWorld->at(y * width + x)) = nullptr;

	SimWorld->at(y * width + x) = element;
}

void Simulation::DeleteElements()
{
	while (!ElementsToDelete->empty())
	{
		Element * e = ElementsToDelete->top();
		

		delete e;
		e = nullptr;

		ElementsToDelete->pop();

	

	}
}




