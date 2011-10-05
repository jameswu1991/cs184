#ifndef sphere_h
#define sphere_h

#include <vector>
#include <math.h>

#include "vertex.h"
#include "ray.h"

using namespace std;

class Sphere {
	Vertex center;
	float radius;
public:
	Sphere ();
	Sphere (Vertex c, float rad);
	
	Vertex normal(Vertex v);
	void scale(float f);
	vector<float> intersect(Ray r);
};

#endif