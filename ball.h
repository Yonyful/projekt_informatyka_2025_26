#include <string>
#include <iostream>

using namespace std;

class ball { // Klasa pi³ki
private:
    double r, x, y, vx, vy, height, width;
public:
    ball(double r_in, double x_in, double y_in, double vx_in, double vy_in, double height, double width); //Konstruktor

    void print(void) { // Debug po³o¿enia pi³ki
        cout << " x: " << x
            << " y: " << y
            << " vx: " << vx
            << " vy: " << vy;
    }


    void bounce(void) { //Symulacja odbicia 
        if (x - r <= 0 || x + r >= width) { //Odbicie w osi X
            vx = -vx;
            cout << " HIT X "; 
        }
        if (y - r <= 0 || y + r >= height) { //Odbicie w osi Y
            vy = -vy;
            cout << " HIT Y ";
        }

    }
    void move_ball(int steps) { //Symulacja ruchu
        for (int i = 1; i <= steps; i++) {
            cout << "Krok " << i;
            print();
            bounce();
            cout << endl;
            x = x + vx;
            y = y + vy;

        }
    }
    double getX(void) { //Getter po³o¿enia na osi x
        return x;
    }
    double getY(void) { //Getter po³o¿enia na osi y
    }


}; //Konstruktor
ball::ball(double r_in, double x_in, double y_in, double vx_in, double vy_in, double height_in, double width_in) {
    r = r_in;
    x = x_in;
    y = y_in;
    vx = vx_in;
    vy = vy_in;
    height = height_in;
    width = width_in;

}