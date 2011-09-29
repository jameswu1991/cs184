#ifndef window_h
#define window_h

#include <vector>
#include <iostream>
#include <math.h>

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

using namespace std;

class Pixel {
public:
	Pixel (int _x, int _y, float _r, float _g, float _b) {
		r = _r;
		g = _g;
		b = _b;
		x = _x;
		y = _y;
	}
	float r;
	float g;
	float b;
	int x;
	int y;
	void print() {
		cout << "[" << x << ", " << y << "] ";
		cout << "(" << r << ", " << g << ", " << b << ")\n";
	}
};

class Window {
private:
	vector<Pixel> pixels;
	static Window* singleton;
	int width;
	int height;
public:
	int getWidth();
	int getHeight();
	void setSize(int w, int h);
	void initialize(int argc, char *argv[]);
	void show();
	void pixel(int x, int y, float r, float g, float b);
	void render();
	static Window* get();
};

#endif