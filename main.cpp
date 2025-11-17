#pragma once
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "paletka.h"
#include "brick.h"
#include "game.h"

int main() {
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "Arkanoid");
	sf::Clock clock; //Implementacja fixed-time steps
	sf::Time timeSinceUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	enum class GameState { Menu, Playing, Scores, Exiting };
	GameState currentState = GameState::Playing;


	Game game;

	while (window.isOpen()) {
		timeSinceUpdate = timeSinceUpdate + clock.restart();
		while (timeSinceUpdate > timePerFrame) {
			timeSinceUpdate = timeSinceUpdate - timePerFrame;
			while (const std::optional event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					window.close();
				}
				else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

					game.handleInput(keyPressed->code, true);
				}
				else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
					game.handleInput(keyReleased->code, false);
				}
			}
			game.update(timePerFrame.asSeconds());

		}

		game.render(window);
		window.display();

	}









}






