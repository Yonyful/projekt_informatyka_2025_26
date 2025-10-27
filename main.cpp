#include <string>
#include <iostream>
#include "ball.h"
#include "paletka.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    //ball b1(10, 0, 3, 5, 5, 50, 50);
    //b1.move_ball(100);
    paletka p1(10, 20, 4, 5, 500, 300);
    p1.move_left(30);
}