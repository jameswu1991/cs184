#ifndef sphere_h
#define sphere_h

#include <vector>
#include <math.h>

#include "vertex.h"
#include "ray.h"

using namespace std;

class Sphere {
public:
	Vertex center;
	float radius;
	Sphere ();
	Sphere (Vertex c, float rad);
	
	Vertex normal(Vertex v);
	Ray intersect(Ray r);
    float intersect_t(Ray r);
	bool intersect_b(Ray r);
	bool unitIntersect_b(Ray r);
	void scale(float f);
};

#endif