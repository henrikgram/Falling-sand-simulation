#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "Elements/Concrete Elements/Sand.h"
#include "Elements/Concrete Elements/Water.h"
#include <Windows.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace std::chrono;

int scale = 4;
sf::RenderWindow window(sf::VideoMode(200 * scale, 200 * scale), "SFML works!");

int main()
{
	int width = 200;
	int height = 200;

	Simulation* sim = new Simulation(width, width);
	//sim->ReplaceElement(new Sand(Vector2i(2, 2)), 2, 2);
	sim->ReplaceElement(new Sand(100,100));
	

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

			sim->ReplaceElement(new Sand(x,y));
		}
		if (Mouse::isButtonPressed(Mouse::Button::Right))
		{
			int x = Mouse::getPosition(window).x / scale;
			int y = Mouse::getPosition(window).y / scale;

			sim->ReplaceElement(new Water(x, y));
		}
	
		window.clear();
		auto start = high_resolution_clock::now();
		//sim->DeleteElements();
		sim->UpdateSimulation();

		auto stop = high_resolution_clock::now();

		auto duration = duration_cast<std::chrono::microseconds>(stop - start);

		std::cout << "Time taken by Update(): "
			<< duration.count() << " microseconds" << std::endl;


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
					else if (type == ElementTag::WATER)
					{
						shape.setFillColor(Color::Blue);
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