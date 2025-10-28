#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "ball.h"
#include "paletka.h"

int main()
{
	
	ball b1(10, 30, 50, 2, 3, 600, 800); //Stworzenie obiektu pi³ka

	sf::RenderWindow window(sf::VideoMode(800, 600), "Moving ball simulation");
	sf::CircleShape shape(static_cast<float>(b1.getR())); //Ustawienie promienia pi³ki
	shape.setFillColor(sf::Color::Green); //Ustawienie koloru
	shape.setPosition(static_cast<float>(b1.getX()), static_cast<float>(b1.getY())); //Ustawienie startowej pozycji pi³ki


	while (window.isOpen())
	{
		window.setFramerateLimit(60);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		b1.move_ball(1); //Ruch pi³ki o jeden krok
		window.clear();
		shape.move(static_cast<float>(b1.getVx()), static_cast<float>(b1.getVy())); //Wizualna zmiana pozycji pi³ki o prêdkoœæ vx i vy
		window.draw(shape);
		window.display();
		
	}
	return 0;
}
