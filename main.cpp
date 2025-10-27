#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "ball.h"
#include "paletka.h"

int main()
{
	
	ball b1(5, 5, 5, 5, 5, 5, 5);
	double r = b1.getR();



	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::CircleShape shape(static_cast<float>(r));
	shape.setFillColor(sf::Color::Green);


	while (window.isOpen())
	{
		window.setFramerateLimit(60);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}
