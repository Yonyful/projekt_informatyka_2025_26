#include <string>
#include <iostream>

using namespace std;

class paletka {
private:
	double x, y, vx, pal_width, width, height;
public:
	paletka(double x_in, double y_in, double  vx_in, double pal_width_in, double width_in, double height_in);

	void print(void) { // Debug po³o¿enia paletki
		cout << " x: " << x
			<< " y: " << y
			<< " vx: " << vx;
	}
	void wall_collision(void) { //Kolizja ze œcian¹
		if (x - pal_width <= 0 || x + pal_width >= width) {
			vx = 0;
			cout << " HIT WALL ";
		}
	}
	void move_left(int steps) { //Ruch w lewo
		double vx_previous = vx;
		for (int i = 1; i <= steps + 1; i++) {
			cout << "Step_left " << i;
			print();
			wall_collision();
			if (vx == 0) {
				break;
			}
			cout << endl;
			x = x - vx;
		}
		vx = vx_previous;
	}
	void move_right(int steps) { //Ruch w prawo
		double vx_previous = vx;
		for (int i = 1; i <= steps; i++) {
			cout << "Step_right " << i;
			print();
			wall_collision();
			if (vx == 0) {
				break;
			}
			cout << endl;
			x = x + vx;
		}
		vx = vx_previous;
	}
};
paletka::paletka(double x_in, double y_in, double  vx_in, double pal_width_in, double width_in, double height_in) { //Konstruktor
	x = x_in;
	y = y_in;
	vx = vx_in;
	pal_width = pal_width_in;
	width = width_in;
	height = height_in;
}


