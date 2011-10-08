#include "model.h"

void Model::addPolygon(Polygon p) {
	polygons.push_back(p);
}

Ray Model::intersect(Ray r) {
	Ray intersection (Vertex(0,0,0), Vertex(0,0,0));
	for (int a=0; a<polygons.size(); a++) {
		float t = polygons[a].intersect(r);
		if (t > 0) {
			Vertex intersect = r.getOrigin().add(r.getDirection().scale(t));
			// cout << t << endl;
			Vertex normal = polygons[a].normal();
			intersection.setOrigin(intersect);
			intersection.setDirection(normal);
			return intersection;
		}
	}
	return intersection;
}

bool Model::intersect_b(Ray r) {
	for (int a=0; a<polygons.size(); a++)
		if (polygons[a].intersect(r) > 0)
			return true;
	return false;
}

void Model::scale(float scale) {
	for (int a=0; a<polygons.size(); a++) 
		polygons[a] = polygons[a].scale(scale);
}
