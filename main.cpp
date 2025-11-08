#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "ball.h"


int main() {
	//Okno


	const float width = 640.f;
	const float height = 480.f;
	sf::RenderWindow window(sf::VideoMode({ (unsigned)width, (unsigned)height }), "test");
	window.setFramerateLimit(60);



	//Obiekty gry
	paletka pal(320.f, 440.f, 5.f, 100.f, 20.f);
	ball ball(8.f, 320.f, 200.f, 4.f, 3.f);



	//Obsluga gry
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { //Paletka prawo-lewo
				pal.move_left();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
				pal.move_right();
			}
			pal.clampToRound(width);
			

			//ball.wallCollision(width, height);
			//if (ball.collidePaddle(pal)) {
			//	cout << "HIT PADDLE\n";
			//}


		}
		ball.move_ball();
		ball.wallCollision(width, height);

		if (ball.collidePaddle(pal)) {
			cout << "HIT PADDLE\n";
		}
		



		window.clear(sf::Color(20, 20, 30));
		pal.draw(window);
		ball.draw(window);
		window.display();

	}
}
