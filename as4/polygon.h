#ifndef polygon_h
#define polygon_h

#include <vector>
#include <math.h>

#include "vertex.h"
#include "ray.h"

using namespace std;

class Polygon {
	vector<Vertex > verticies;
public:
	void addPoint(Vertex v);
	vector<Vertex > getVerticies();
	void print();
	Vertex normal();
	Vertex center();
	Polygon translate(Vertex v);
	Polygon scale(float x, float y, float z);
	float intersect(Ray r);
	Polygon rotate(Vertex rotation);
	Polygon eRotate(vector<Vertex> eulerAngles);
};

#endif
