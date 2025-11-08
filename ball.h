#pragma once
#include <string>
#include <iostream>
#include "paletka.h"

using namespace std;

class ball { // Klasa pi³ki
private:
    float r, x, y, vx, vy;
    sf::CircleShape shape;
public:
    ball(float r_in, float x_in, float y_in, float vx_in, float vy_in); //Konstruktor

    void print(void) { // Debug po³o¿enia pi³ki
        cout << " x: " << x
            << " y: " << y
            << " vx: " << vx
            << " vy: " << vy
            << endl;
    }


    void bounceX(void) { //Odbicie X i Y
        vx = -vx;
    }
    void bounceY(void) {
        vy = -vy;
    }


    void wallCollision(float width, float height) { //Kolizja ze scianami 
        if (x - r  <= 0) { //Kolizja pozioma
            bounceX();
        }
        else if (x + r >= width) {
            bounceX();
        }

        if (y - r <= 0) { //Kolizja pionowa oraz ustawienie pozycji zeby pilka nie byla w scianie
            bounceY();
        }
        else if (y + r >= height) {
            bounceY();
        }
    }


    bool collidePaddle(paletka& p) { //Kolizja paletka pilka 
        if (x + r >= p.getX() - (p.getpal_width() / 2) &&  x - r <= p.getX() + (p.getpal_width() / 2) && y + r >= p.getY() - (p.getpal_height() / 2) &&  y - r < p.getY() - (p.getpal_height() / 2)){
            vy = -abs(vy);                                 
            y = p.getY() - (p.getpal_height() / 2) - r;     
            shape.setPosition({ x, y });
            return true;
        }
        else {
            return false;
        }

    }


    void move_ball(void) { //Ruch pilki
            x = x + vx;
            y = y + vy;
            shape.setPosition({ x,y });
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
    float getR(void) {
        return r;
    }
    float getVx(void) {
        return vx;
    }
    float getVy(void) {
        return vy;
    }
    sf::CircleShape& getShape() {
        return shape;
    }
    



}; //Konstruktor
ball::ball(float r_in, float x_in, float y_in, float vx_in, float vy_in) {
    r = r_in;
    x = x_in;
    y = y_in;
    vx = vx_in;
    vy = vy_in;


    shape.setRadius({ r_in });
    shape.setOrigin({ r_in, r_in });
    shape.setPosition({ x_in, y_in });
    shape.setFillColor(sf::Color::White);

}