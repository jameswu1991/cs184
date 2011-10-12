#ifndef model_h
#define model_h

#include <vector>
#include <iostream>
#include <math.h>

#include "polygon.h"
#include "ray.h"

using namespace std;

class Model {
	vector<Polygon> polygons;
public:
	void addPolygon(Polygon p);
	void scale(float x, float y, float z);
	void rotate(Vertex rotation);
	Ray intersect(Ray r);
	bool intersect_b(Ray r);
};

#endif
