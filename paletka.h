#pragma once
#include <string>
#include <iostream>
 

using namespace std;

class paletka {
private:
	float x, y, vx, pal_width, pal_height;
	sf::RectangleShape shape;
public:
	paletka(float x_in, float y_in, float  vx_in, float pal_width_in, float pal_height_in);

	void print(void) { // Debug po³o¿enia paletki
		cout << " x: " << x
			<< " y: " << y
			<< " vx: " << vx
			<< endl;
			
	}

	void clampToRound(float width) { //Blokada wyjscia za scianê
		if (x - pal_width / 2 <= 0) {
			x = pal_width / 2;
			shape.setPosition({ x, y });
		}
		if (x + pal_width / 2 >= width) {
			x = width - (pal_width / 2);
			shape.setPosition({ x, y });
		}
	}

	void move_left(float distance) { //Ruch w lewo
		x = x - distance;
		shape.setPosition({ x, y });
	}

	void move_right(float distance) { //Ruch w prawo
		x = x + distance;
		shape.setPosition({ x, y });
	}

	void draw(sf::RenderTarget& target) { //Rysowanie
		target.draw(shape);
	}


	float getX(void) { //Gettery
		return x;
	}
	float getY(void) { 
		return y;
	}
	float getpal_width(void){
		return pal_width;
	}
	float getpal_height(void) {
		return pal_height;
	}
	float getVx(void) {
		return vx;
	}
	sf::RectangleShape& getShape(){ 
		return shape; 
	}

};
paletka::paletka(float x_in, float y_in, float  vx_in, float pal_width_in, float pal_height_in) { //Konstruktor
	x = x_in;
	y = y_in;
	vx = vx_in;
	pal_width = pal_width_in;
	pal_height = pal_height_in;

	
	shape.setSize({ pal_width_in, pal_height_in }); //Parametry paletki w SFML
	shape.setOrigin({ pal_width_in / 2, pal_height_in / 2 });
	shape.setPosition({ x_in, y_in });
	shape.setFillColor(sf::Color::Red);
}


