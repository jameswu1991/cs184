#ifndef ray_h
#define ray_h

#include <vector>

#include "vertex.h"

class Ray {
private:
	Vertex origin;
	Vertex direction;
public:
	Ray (Vertex p0, Vertex p1);
	Vertex getOrigin();
	Vertex getDirection();
	void setOrigin(Vertex o);
	void setDirection(Vertex d);
};

#endif