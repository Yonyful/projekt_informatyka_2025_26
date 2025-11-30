#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "ball.h"
#include "paletka.h"
#include "brick.h"




class Game {
private:
	sf::RenderWindow& window;
	paletka pal;
	ball bl;
	bool movingLeft, movingRight;
	std::vector<Brick> bricks;
	bool isExiting = false;



	void processEvents() { //Obs³uga eventów
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
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
		if (key == sf::Keyboard::Key::Escape) {
			isExiting = true;
		}

	}

	void generateBricks() { //Generacja wektora z cegielkami 
		const int columns = 6;
		const int rows = 7;
		const float brick_size_y = 25.f;
		const float brick_size_x = (640.f - (columns - 1) * 2.f) / columns;
		float posY = brick_size_y / 2 + 50.f;

		for (int i = 0; i < rows; i++) { //Ustawianie pozycji poszczegolnych cegielek
			float posX = brick_size_x / 2;

			for (int j = 0; j < columns; j++) {

				int L = (i < 1) ? 3 : (i < 3) ? 2 : 1;
				bricks.emplace_back(sf::Vector2f{ posX , posY }, sf::Vector2f{ brick_size_x, brick_size_y }, L);
				posX = posX + brick_size_x + 2.f;
			}
			posY = posY + brick_size_y + 2.f;

		}



	}

	void update(float deltaTime) { //Funkcja aktualizujaca obiekty

		if (movingLeft == true) { //Ruch paletki w lewo i prawo
			pal.move_left(deltaTime * 50 * pal.getVx());
		}
		if (movingRight == true) {
			pal.move_right(deltaTime * 50 * pal.getVx());
		}
		pal.clampToRound(640); //Blokada wychodzenia paletki poza ekran 

		bl.move_ball(deltaTime * 50 * bl.getVx(), deltaTime * 50 * bl.getVy()); //Ruch pi³ki

		bl.wallCollision(640, 480); //Kolizja paletki ze sciana
		if (bl.collidePaddle(pal)) {
			std::cout << "HIT PADDLE\n";
		}
		for (auto& brick : bricks) {
			if (bl.collideBrick(brick) == true) {
				brick.hit();
				break;
			}
		}
		



		if ((bl.getY() + bl.getR()) >= 480) { //Przegrana

			//window.close();
		}
	}
	void render() { //Renderowanie obiektów
		window.setFramerateLimit(60);
		window.clear(sf::Color(20, 20, 30));
		pal.draw(window);
		bl.draw(window);
		for (auto& brick : bricks) {
			brick.draw(window);
		}
		window.display();
	}


	sf::Clock clock; //Zegar
	sf::Time timeSinceUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);



public: //Uruchomienie gry
	Game(sf::RenderWindow& win);
	void run() {
		isExiting = false;
		sf::Time delta = clock.restart();

		if (delta > sf::seconds(0.1f)) { //Ograniczenie dlugosci delty czasu 
			delta = sf::seconds(0.1f);
		}

		timeSinceUpdate += delta;
		while (timeSinceUpdate > timePerFrame) {
			timeSinceUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame.asSeconds());
		}
		render();
	}
	bool is_exiting() { //Gettery
		return isExiting;
	}
	paletka& getPaddle() {
		return pal;
	}
	ball& getBall() {
		return bl;
	}
	std::vector<Brick>& getBricks() {
		return bricks;
	}



};
Game::Game(sf::RenderWindow& win):window(win), pal(320.f, 440.f, 5.f, 100.f, 20.f),
	bl(8.f, 320.f, 400.f, 4.f, 3.f),
	movingLeft(false),
	movingRight(false)
{
	generateBricks();
}