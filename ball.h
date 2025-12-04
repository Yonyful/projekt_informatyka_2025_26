#pragma once
#include <string>
#include <iostream>
#include "paletka.h"
#include "brick.h"

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

        if (y - r <= 0) { //Kolizja pionowa 
            bounceY();
        }
        else if (y + r >= height) {
            bounceY();
        }
    }


    bool collidePaddle(paletka& p) { //Kolizja pilki z paletka 
        float left = p.getX() - (p.getpal_width() / 2.f);
        float right = p.getX() + (p.getpal_width() / 2.f);
        float top = p.getY() - (p.getpal_height() / 2.f);

        if (x + r >= left &&  x - r <= right && y + r >= top &&  y - r < p.getY() - (p.getpal_height() / 2)){
            vy = -abs(vy);                                 
            y = p.getY() - (p.getpal_height() / 2) - r;     
            shape.setPosition({ x, y });
            return true;
        }
        else {
            return false;
        }

    }

    bool collideBrick(Brick& b) { //Kolizja z brickiem

        float width = b.getSize().x; //Wymiary klocka
        float height = b.getSize().y;
        float left = b.getPosition().x - width / 2.f;
        float right = b.getPosition().x + width / 2.f;
        float top = b.getPosition().y - height / 2.f;
        float bottom = b.getPosition().y + height / 2.f;

        if (b.getisDestroyed() == false) {
            if (x + r >= left && x - r <= right && y + r >= top && y - r <= bottom) {
                if (y < b.getPosition().y) {
                    vy = -abs(vy);
                    y = top - r;
                }
                else {
                    vy = abs(vy);
                    y = bottom + r;
                }


                shape.setPosition({ x, y });
                return true;
            }
            return false;
        }

      
    }
    void move_ball(float distanceX, float distanceY) { //Ruch pilki
            x = x + distanceX;
            y = y + distanceY;
            shape.setPosition({ x , y });
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


    void reset(float xreset, float yreset, float vxreset, float vyreset) { //Setter 
        x = xreset;
        y = yreset;
        vx = vxreset;
        vy = vyreset;
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