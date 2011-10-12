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
	Vertex (float x, float y, float z, float r, float g, float b);
	Vertex (float r[], int length);
	Vertex (vector<float> _data);
	
	Vertex add(Vertex v);
	Vertex sub(Vertex v);
	Vertex mul(Vertex v);
	Vertex divi(Vertex v);
	Vertex scale(float s);
	Vertex scale(float x, float y, float z);
	
	Vertex cross(Vertex v);
	float dot(Vertex v);
	float sum();
	float magnitude();
	
	Vertex normalize();
	Vertex invert();
	Vertex reflect(Vertex l);
	Vertex eRotate(vector<Vertex> eulerAngles);
	Vertex rotate(Vertex rotation);
	
	int size();
	float get(int index);
	vector<float> getData();
	void print();
	bool isNull();
};

#endif
