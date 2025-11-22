#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "ball.h"
#include "paletka.h"
#include "brick.h"

class Game {
private:
	paletka pal;
	ball ball;
	bool movingLeft, movingRight;
	std::vector<Brick> bricks;
	bool is_game_exiting = false;




public: //Uruchomienie gry
	Game();
	void update(float deltaTime) { //Funkcjonalnoœæ gry
		if (movingLeft == true) { //Ruch paletki w lewo i prawo
			pal.move_left(deltaTime * 1 * pal.getVx());
		}
		if (movingRight == true) {
			pal.move_right(deltaTime * 1 * pal.getVx());
		}
		pal.clampToRound(640); //Blokada wychodzenia paletki poza ekran 

		ball.move_ball(deltaTime * 1 * ball.getVx(), deltaTime * 1 * ball.getVy()); //Ruch pi³ki

		ball.wallCollision(640, 480); //Kolizja paletki ze sciana
		ball.collidePaddle(pal);
		for (auto& brick : bricks) {
			if (ball.collideBrick(brick) == true) {
				brick.hit();
				break;
			}
		}
		if ((ball.getY() + ball.getR()) >= 480) { //Przegrana
			is_game_exiting = true;
			std::cout << "Przegrana"; 
		}
	}
	void render(sf::RenderTarget& target) { //Renderowanie obiektów
		target.clear(sf::Color(20, 20, 30));
		pal.draw(target);
		ball.draw(target);
		for (auto& brick : bricks) {
			brick.draw(target);
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
			is_game_exiting = true;
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
	bool return_is_game_exiting(void) {
		return is_game_exiting;
	}
	void reset() {
		pal.setPosition({ 320.f, 440.f });
		pal.setVelocity(300.f);  
		ball.setPosition({ 320.f, 400.f });
		ball.setVelocity({ 200.f, -150.f }); 
		movingLeft = false;
		movingRight = false;
		is_game_exiting = false;
		bricks.clear();
		generateBricks();
	}




};
Game::Game() : pal(320.f, 440.f, 300.f, 100.f, 20.f),
	ball(8.f, 320.f, 400.f, 200.f, -150.f),
	movingLeft(false),
	movingRight(false)
{
	generateBricks();
}