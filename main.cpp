#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "ball.h"
#include "paletka.h"

class Game {
private:
	sf::RenderWindow window;
	paletka pal;
	ball ball;

	void processEvents() { //Procesowanie okna
			while (const std::optional event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					window.close();
				}
			}
	}
	void update() { //Funkcjonalnoœæ gry


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { //Paletka prawo-lewo
			pal.move_left();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			pal.move_right();
		}
		pal.clampToRound(640);


		ball.move_ball(); //Ruch pi³ki
		ball.wallCollision(640, 480);
		if (ball.collidePaddle(pal)) {
			std::cout << "HIT PADDLE\n";
		}

		if ((ball.getY() + ball.getR()) >= 480 ) {

			window.close();
		}
		
		


	}
	void render() { //Renderowanie obiektów
		window.setFramerateLimit(60);
		window.clear(sf::Color(20,20,30));
		window.draw(pal.getShape());
		window.draw(ball.getShape());
		window.display();
	}


public: //Uruchomienie gry
	Game();
	void run() { 
		while (window.isOpen()) {
			processEvents();
			update();
			render();

		}
	}
};


Game::Game() :window(sf::VideoMode({ 640, 480 }), "test"), pal(320.f, 440.f, 5.f, 100.f, 20.f), ball(8.f, 320.f, 200.f, 4.f, 3.f) //Konstruktor
{

}



int main() {
	Game game;
	game.run();


}