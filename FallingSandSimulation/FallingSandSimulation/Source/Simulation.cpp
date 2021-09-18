#include "Simulation.h"
#include "Elements/Concrete Elements/Empty.h"

Simulation::Simulation(int width, int height)
{
	this->width = width;
	this->height = height;

	SimWorld = new std::vector<Element*>(width * height);
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			SimWorld->at(y * width + x) = new Empty(Vector2i(x, y));
		}
	}
}

ElementTag Simulation::GetElementTag(int x, int y)
{
	return SimWorld->at(y * width + x)->GetTag();
}

void Simulation::SetElement(Element* element, int y, int x)
{
	delete SimWorld->at(y * width + x);
	SimWorld->at(y * width + x) = nullptr;
	
	SimWorld->at(y * width + x) = element;
}




