#ifndef vertex_h
#define vertex_h

#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

class Vertex {
	vector<float> data;
public:
	Vertex ();
	Vertex (float x, float y, float z);
	Vertex (float r[], int length);
	Vertex (vector<float> _data);
	
	Vertex add(Vertex v);
	Vertex sub(Vertex v);
	Vertex mul(Vertex v);
	Vertex scale(float f);
	
	Vertex cross(Vertex v);
	float dot(Vertex v);
	float sum();
	float magnitude();
	
	Vertex normalize();
	Vertex invert();
	
	int size();
	float get(int index);
	vector<float> getData();
	void print();
};

#endif