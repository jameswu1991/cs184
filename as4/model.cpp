#include "model.h"

void Model::addPolygon(Polygon p) {
	polygons.push_back(p);
}

bool Model::intersect(Ray r) {
	for (int a=0; a<polygons.size(); a++) {
		if (polygons[a].intersect(r))
			return true;
	}
	return false;
}