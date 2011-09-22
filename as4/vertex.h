#ifndef vertex_h
#define vertex_h

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

class Vertex {
	vector<float> data;
public:
	Vertex (float x, float y, float z);
	Vertex (float r[], int length);
	Vertex (vector<float> _data);
	
	Vertex add(Vertex v);
	Vertex sub(Vertex v);
	Vertex mul(Vertex v);
	Vertex scale(float f);
	
	Vertex normalize();
	float dot(Vertex v);
	float sum();
	float magnitude();
	
	void print();
	void draw();
};

#endif