#include "model.h"

void Model::addPolygon(Polygon p) {
	polygons.push_back(p);
}

Ray Model::intersect(Ray r) {
	Ray intersection (Vertex(0,0,0), Vertex(0,0,0));
	float lowestT = 100000;
	for (int a=0; a<polygons.size(); a++) {
		float t = polygons[a].intersect(r);
		if (t > 0 && t < lowestT) {
			Vertex intersect = r.getOrigin().add(r.getDirection().scale(t - 0.0001));
			Vertex normal = polygons[a].normal();
			intersection.setOrigin(intersect);
			intersection.setDirection(normal);
			lowestT = t;
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

float Model::intersect_t(Ray r) {
	float lowestT = 0;
	for (int a=0; a<polygons.size(); a++) {
		float t = polygons[a].intersect(r);
		if (t > 0 && (lowestT == 0 || t < lowestT)) {
			lowestT = t;
		}
	}
	return lowestT;
}

void Model::translate(float x, float y, float z) {
	for (int a=0; a<polygons.size(); a++) 
		polygons[a] = polygons[a].translate(Vertex(x, y, z));
}

void Model::scale(float x, float y, float z) {
	for (int a=0; a<polygons.size(); a++) 
		polygons[a] = polygons[a].scale(x, y, z);
}

void Model::rotate(Vertex rotation) {
	/*
	// regular, not-fast rotation
	for (int a=0; a<polygons.size(); a++) 
		polygons[a] = polygons[a].rotate(rotation);
	*/
	
	// euler angle rotations
	float xrot = rotation.get(0);
	float yrot = rotation.get(1);
	float zrot = rotation.get(2);
	
	Vertex xvert1 (1, 0, 0);
	Vertex xvert2 (0, cos(xrot), sin(xrot));
	Vertex xvert3 (0, -sin(xrot), cos(xrot));
	Vertex yvert1 (cos(yrot), 0, -sin(yrot));
	Vertex yvert2 (0, 1, 0);
	Vertex yvert3 (sin(yrot), 0, cos(yrot));
	Vertex euler1 (cos(zrot), -sin(zrot), 0);
	Vertex euler2 (sin(zrot), cos(zrot), 0);
	Vertex euler3 (0, 0, 1);
	
	euler1 = Vertex (euler1.dot(yvert1), euler1.dot(yvert2), euler1.dot(yvert3));
	euler2 = Vertex (euler2.dot(yvert1), euler2.dot(yvert2), euler2.dot(yvert3));
	euler3 = Vertex (euler3.dot(yvert1), euler3.dot(yvert2), euler3.dot(yvert3));
	euler1 = Vertex (euler1.dot(xvert1), euler1.dot(xvert2), euler1.dot(xvert3));
	euler2 = Vertex (euler2.dot(xvert1), euler2.dot(xvert2), euler2.dot(xvert3));
	euler3 = Vertex (euler3.dot(xvert1), euler3.dot(xvert2), euler3.dot(xvert3));

	vector<Vertex> eulerAngles(3);
	eulerAngles[0] = euler1;
	eulerAngles[1] = euler2;
	eulerAngles[2] = euler3;
	for (int a=0; a<polygons.size(); a++) 
		polygons[a] = polygons[a].eRotate(eulerAngles);
}
