#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "Elements/Concrete Elements/Sand.h"
int scale = 4;
sf::RenderWindow window(sf::VideoMode(200 * scale, 200 * scale), "SFML works!");

int main()
{


	Simulation* sim = new Simulation(200, 200);
	sim->SetElement(new Sand(Vector2i(100, 100)), 100, 100);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	

	
		window.clear();

		//RectangleShape shape(Vector2f(1 * scale, 1 * scale));
		//shape.setPosition(Vector2f(100 * scale, 100 * scale));
		//shape.setFillColor(Color::Yellow);
		//window.draw(shape);
		//window.display();

		for (int y = 0; y < 200; y++)
		{
			for (int x = 0; x < 200; x++)
			{

				ElementTag type = sim->GetElementTag(x, y);
				//ElementTag type = ElementTag::SAND;
			

				if (type == ElementTag::EMPTY)
				{
					continue;
				}

				else
				{
					RectangleShape shape(Vector2f(1 * scale, 1 * scale));
					shape.setPosition(Vector2f(x * scale, y * scale));
					shape.setFillColor(Color::Yellow);
					window.draw(shape);

					if (type == ElementTag::SAND)
					{
						shape.setFillColor(Color::Yellow);

					}
					else
					{
						int pik = 4;
					}

					

					
				}
			}


			
		}
			
		window.display();
		
		
	}

	return 0;
}