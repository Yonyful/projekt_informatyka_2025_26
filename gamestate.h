#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <fstream>
#include "paletka.h"
#include "ball.h"
#include "brick.h"



struct BlockData {
	float x, y;
	int hp;
};

class SaveState {
private:
	sf::Vector2f paddlePosition;
	sf::Vector2f ballPosition;
	sf::Vector2f ballVelocity;
	std::vector<BlockData> blocks;
	const float size_x = 105.f;
	const float size_y = 25.f;

public:
	SaveState(paletka&p, ball& b, std::vector<Brick>& bricks);



	bool saveToFile(const std::string& filename) { //Zapis do pliku
		std::ofstream file(filename);
		if (!file.is_open()) { //Zwrocenie false gdy nie udalo sie otworzyc pliku 
			std::cout << "Nie mozna otworzyc pliku" << filename << "\n";
			return false;
		}
		file << "PADDLE" << " " <<  paddlePosition.x << " " << paddlePosition.y << "\n"; //Zapis parametrow paletki
		file << "BALL" << " " << ballPosition.x << " " << ballPosition.y << " " //Zapis parametrow pilki
			<< ballVelocity.x << " " << ballVelocity.y << "\n";
		file << "BRICKS_COUNT" << " " << blocks.size() << "\n"; //Ilosc cegielek
		
		for (const auto& block : blocks) {
			file << "BRICK" << " " << block.x << " " << block.y << " " << block.hp << "\n";
		}
		file.close();
		return true;
	}

	bool loadFromFile(const std::string& filename) {  //Odczyt z pliku
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cout << "Nie mozna otworzyc pliku" << filename << "\n";
			return false;
		}
		std::string label;


		if (!(file >> label  //Wczytanie paletki
			>> paddlePosition.x  
			>> paddlePosition.y)) {
			std::cout << "Blad odczytu paddle\n";
			return false;
		}
		if (!(file >> label >> ballPosition.x  //Wczytanie pilki
			>> ballPosition.y 
			>> ballVelocity.x 
			>> ballVelocity.y )) {
			std::cout << "Blad odczytu ball\n";
			return false;
		}

		int blocksCount;

		if (!(file >> label >> blocksCount)) { //Wczytanie ilosci cegiel
			std::cout << "Blad odczytu bricks_count\n";
			return false;
		}

		blocks.clear(); //Wczytanie cegiel
		for (int i = 0; i < blocksCount; ++i) {
			float x, y;
			int hp;
			if (!(file >> label 
				>> x 
				>> y  
				>> hp )) {
				std::cout << "Blad odczytu bricks\n";
				return false;
			}
			blocks.push_back({x , y , hp});
		}
		file.close();
		return true;
	}
	void apply(paletka& p, ball& b, std::vector<Brick>& bricks) { //Przypisanie wszystkich pozycji 
		p.setPosition(paddlePosition.x, paddlePosition.y);
		b.reset(ballPosition.x, ballPosition.y, ballVelocity.x, ballVelocity.y);
		bricks.clear();
		sf::Vector2f size(size_x, size_y);
		for (const auto& data : blocks) {
			if (data.hp != 0) {
			bricks.emplace_back(sf::Vector2f(data.x, data.y), size, data.hp);
			}
			
		}


	}

}; 
SaveState::SaveState(paletka& p,ball& b, std::vector<Brick>& bricks) { //Konstruktor pobierajacy wszystkie aktualne pozycje obiektow gry
	paddlePosition.x = p.getX();
	paddlePosition.y = p.getY();
	ballPosition.x = b.getX();
	ballPosition.y = b.getY();
	ballVelocity.x = b.getVx();
	ballVelocity.y = b.getVy();

	for (auto& br : bricks) {
		blocks.emplace_back(BlockData{br.getPosition().x, br.getPosition().y, br.getHP()});
	}

}