#ifndef polygon_h
#define polygon_h

#include <vector>
#include <math.h>

#include "vertex.h"

using namespace std;

class Polygon {
	vector<Vertex > verticies;
public:
	void addPoint(Vertex v);
	vector<Vertex > getVerticies();
	void print();
	void draw();
	Polygon translate(Vertex v);
	Polygon scale(float v);
};

#endif