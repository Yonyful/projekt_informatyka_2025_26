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
	bool movingLeft, movingRight;
	


	void processEvents() { //Obs³uga eventów
			while (const std::optional event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					window.close();
				}
				else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
				
					handleInput(keyPressed->code, true);
				}
				else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
					handleInput(keyReleased->code, false);
				}
			}
	}

	void handleInput(sf::Keyboard::Key key, bool isPressed) {  //Obs³uga nacisniêc przycisków
		if (key == sf::Keyboard::Key::A) {
			movingLeft = isPressed;
		}
		if (key == sf::Keyboard::Key::D) {
			movingRight = isPressed;
		}

	}

	void update(float deltaTime) { //Funkcjonalnoœæ gry
		
		if (movingLeft == true) {
			pal.move_left(deltaTime * 50 * pal.getVx() );
		}
		if (movingRight == true) {
			pal.move_right(deltaTime * 50 * pal.getVx());
		}
		pal.clampToRound(640);

		ball.move_ball(deltaTime * 50 * ball.getVx(), deltaTime * 50 * ball.getVy()); //Ruch pi³ki

		ball.wallCollision(640, 480);
		if (ball.collidePaddle(pal)) {
			std::cout << "HIT PADDLE\n";
		}

		if ((ball.getY() + ball.getR()) >= 480 ) {

			//window.close();
		}
	}
	void render() { //Renderowanie obiektów
		window.setFramerateLimit(60);
		window.clear(sf::Color(20,20,30));
		window.draw(pal.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	sf::Clock clock;
	sf::Time timeSinceUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	


public: //Uruchomienie gry
	Game();
	void run() { 
		while (window.isOpen()) {
			processEvents();
			timeSinceUpdate = timeSinceUpdate + clock.restart();

			while (timeSinceUpdate > timePerFrame) {
				timeSinceUpdate = timeSinceUpdate - timePerFrame;
				processEvents();
				update(timePerFrame.asSeconds());
			}

			render();

		}
	}
};
Game::Game():window(sf::VideoMode({ 640, 480 }), //Konstruktor gry
	"test"), pal(320.f, 440.f, 5.f, 100.f, 20.f),
	ball(8.f, 320.f, 200.f, 4.f, 3.f),
	movingLeft(false),
	movingRight(false)
{

}




int main() {
	Game game;
	game.run();


}