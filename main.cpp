#pragma once
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "paletka.h"
#include "brick.h"
#include "game.h"
#include "menu.h"

int main() {
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "Arkanoid");
	sf::Clock clock; 
	sf::Time timeSinceUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	enum class GameState { Menu, Playing, Scores, Exiting };
	GameState currentState = GameState::Menu;


	Game game;
	Menu menu(window.getSize().x, window.getSize().y);
	int menu_selected_flag = 0;

	while (window.isOpen()) {
		switch (currentState) {
		case GameState::Menu: //Case - menu
			while (const std::optional event = window.pollEvent())
			{
				// Jezeli odebrano zdarzenie "Closed" zamknij okno
				if (event->is<sf::Event::Closed>())
					window.close();
				//jezeli nacisnieto jakikolwiek przycisk
				if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
				{//Obsluga menu z poziomu klawiszy (strzalki)
					if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
					{
						myDelay(100);
						menu.przesunG();
					}

					if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
					{
						myDelay(100);
						menu.przesunD();
					}
					if (menu_selected_flag == 0)
					{//uruchamianie procedur na skutek wyboru menu (wybor poziomu menu to ENTER))
						if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 0)
						{
							std::cout << "Uruchamiam gre..." << std::endl;
							menu_selected_flag = 1;
							currentState = GameState::Playing;
							clock.restart();
							game.reset();
							timeSinceUpdate = sf::Time::Zero;
						}

						if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 1)
						{
							std::cout << "Najlepsze wyniki..." << std::endl;
							menu_selected_flag = 1;
							currentState = GameState::Scores;
						}

						if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 2)
						{
							std::cout << "Koniec gry..." << std::endl;
							menu_selected_flag = 1;
							currentState = GameState::Exiting;
						}

					}


				}
			}
			window.clear(); //Renderowanie
			if (menu_selected_flag == 0) {
				menu.draw(window);
			}
			window.display();
			break;

		case GameState::Playing: //Arkanoid, case - playing
			timeSinceUpdate = timeSinceUpdate + clock.restart();
			while (timeSinceUpdate > timePerFrame) { //Update gry tylko w stalych ramach czasowych 
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
					if (game.return_is_game_exiting() == true) {
						menu_selected_flag = 0;
						currentState = GameState::Menu;
					}
				}
				game.update(timePerFrame.asSeconds());

			}
			game.render(window); //Renderowanie 
			window.display();
			break;

		case GameState::Exiting: //Wyjscie z gry
			window.close();
			break;
		case GameState::Scores: //Tablica wynikow
			break;

		} 
		
	}

}






