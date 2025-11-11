#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>




class Brick : public sf::RectangleShape {
private:
	int health_points;
	bool isDestroyed;
	static const std::array<sf::Color, 4> colorLUT; //Tablica mapujaca health_points na kolor

public:
	Brick(sf::Vector2f startPos, sf::Vector2f size, int Life);

	void hit() { //Trafienie przez pilke
		if (isDestroyed == true) {
			return;
		}
		health_points = health_points - 1;
		updateColor();
		if (health_points == 0) {
			isDestroyed = true;
		}
	}


	void updateColor() { //Ustawianie koloru
		if (health_points >= 0 && health_points < 4) {
			this->setFillColor(colorLUT[health_points]);
		}
	}

	void draw(sf::RenderTarget& target) {
		if (isDestroyed == false) {
			target.draw(*this);
		}
	}


	bool getisDestroyed() { //Getter zmiennej isDestroyed
		return isDestroyed;
	}

	sf::Vector2f getSize() { //Gettery rozmiaru i pozycji klocka 
		return sf::RectangleShape::getSize();
	}
	sf::Vector2f getPosition() {
		return sf::RectangleShape::getPosition();
	}


};
Brick::Brick(sf::Vector2f startPos, sf::Vector2f size, int Life) {  //Konstruktor 
	isDestroyed = false;
	health_points = Life;
	this->setPosition(startPos);
	this->setSize(size);
	this->setOrigin({ this->getSize().x / 2 , this->getSize().y / 2 });
	this->setOutlineThickness(2.f);
	updateColor();

}


const std::array<sf::Color, 4> Brick::colorLUT = { //Lista 

sf::Color::Transparent, 
sf::Color::Red, 
sf::Color::Yellow, 
sf::Color::Blue 

};

