#pragma once
#include <SFML/Graphics.hpp>s
#include <string>
#include <iostream>
#include <vector>
#include "game.h"
#include "menu.h"
#include "gamestate.h"


int main() {
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "Arkanoid");
	enum class GameState {Menu, Playing, Scores};
	GameState currentState = GameState::Menu;
	int menu_selected_flag = 0;
	Game game(window);
	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen()) {
		switch (currentState) {
		case GameState::Menu:
			menu_selected_flag = 0;
			while (const std::optional event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					window.close();
				}

				if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
					if (keyPressed->scancode == sf::Keyboard::Scancode::Up) { //Przesuniecie gora
						myDelay(100);
						menu.przesunG();
					}
					if (keyPressed->scancode == sf::Keyboard::Scancode::Down) { //Przesuniecie dol
						myDelay(100);
						menu.przesunD();
					}

					if (menu_selected_flag == 0) {
						if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 0) { //Zmiana gamestate
							std::cout << "Uruchamiam gre..." <<  std::endl;
							menu_selected_flag = 1;
							currentState = GameState::Playing;
						}
						if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 1) {
							std::cout << "Wczytuje gre..." << std::endl;

							SaveState temp(game.getPaddle(), game.getBall(), game.getBricks()); //Wczytywanie gry, w tym celu wykorzystany jest tymczasowy savestate
							if (temp.loadFromFile("zapis.txt")) {
								temp.apply(game.getPaddle(), game.getBall(), game.getBricks());
								std::cout << "Gra wczytana!" << std::endl;

								menu_selected_flag = 1;
								currentState = GameState::Playing;
							}
							else {
								std::cout << "Brak zapisu. " << std::endl;
							}
						}

						if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 2) {
							std::cout << "Najlepsze wyniki..." << std::endl;
							menu_selected_flag = 1;
							currentState = GameState::Scores;
						}
						if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 3) {
							std::cout << "Koniec gry..." << std::endl;
							menu_selected_flag = 1;
							window.close();
						}
					}
				}
			}
			window.clear(); //Procedury rysujace menu
			if (menu_selected_flag == 0) {
				menu.draw(window);
			}
			window.display();
			break;





		case GameState::Playing: 
			game.run(); //Uruchomienie gry
			if (game.is_exiting() == true) { //Powrot do menu i zapis gry
				SaveState saveState(game.getPaddle(), game.getBall(), game.getBricks());
				saveState.saveToFile("zapis.txt");
				std::cout << "Gra zapisana!" << "\n";
				currentState = GameState::Menu;
			}
			break;

		case GameState::Scores:
			break;
		}


	}

}