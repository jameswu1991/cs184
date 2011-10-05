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
	Vertex intersect(Ray r);
};

#endif