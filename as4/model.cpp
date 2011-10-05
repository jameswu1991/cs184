#include "model.h"

void Model::addPolygon(Polygon p) {
	polygons.push_back(p);
}

Vertex Model::intersect(Ray r) {
	for (int a=0; a<polygons.size(); a++) {
		if (polygons[a].intersect(r) > 0) {
			return polygons[a].normal();
		}
	}
	return Vertex (0, 0, 0);
}