#include "ray.h"

Ray::Ray(Vertex p0, Vertex p1) {
	origin = p0;
	direction = p1.sub(p0);
}

Vertex Ray::getOrigin() {
	return origin;
}

Vertex Ray::getDirection() {
	return direction;
}

void Ray::setOrigin(Vertex o) {
	origin = o;
}

void Ray::setDirection(Vertex d) {
	direction = d;
}
