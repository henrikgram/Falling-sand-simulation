#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "Elements/Concrete Elements/Sand.h"
int scale = 4;
sf::RenderWindow window(sf::VideoMode(200 * scale, 200 * scale), "SFML works!");

int main()
{
	int width = 200;
	int height = 200;

	Simulation* sim = new Simulation(width, width);
	//sim->SetElement(new Sand(Vector2i(2, 2)), 2, 2);
	sim->SetElement(new Sand(100,100));
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

	
	
		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			int x = Mouse::getPosition(window).x / scale;
			int y = Mouse::getPosition(window).y / scale;

			sim->SetElement(new Sand(x,y));
		}
	
		window.clear();
		//sim->DeleteElements();
	
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
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
				

					if (type == ElementTag::SAND)
					{
						shape.setFillColor(Color::Yellow);

					}
					else
					{
						int pik = 4;
					}

					window.draw(shape);

					
				}
			}


			
		}
			
		window.display();
		
		
	}

	return 0;
}