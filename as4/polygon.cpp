#include "polygon.h"

void Polygon::addPoint(Vertex v) {
	verticies.push_back(v);
}

vector<Vertex> Polygon::getVerticies() {
	return verticies;
}

void Polygon::print() {
	cout << "[";
	for (int i=0; i<verticies.size(); i++) {
		verticies[i].print();
		cout << "\t";
	}
	cout << "]" << endl;
}

Vertex Polygon::normal() {
	if (verticies.size() == 0)
		throw 1;
	Vertex basis1 = verticies[1].sub(verticies[0]);
	Vertex basis2 = verticies[2].sub(verticies[0]);
	return basis1.cross(basis2).normalize();
}

Polygon Polygon::translate(Vertex v) {
	Polygon p;
	for (int i=0; i<verticies.size(); i++) {
		p.addPoint(verticies[i].add(v));
	}
	return p;
}

Polygon Polygon::scale(float f) {
	Polygon p;
	for (int i=0; i<verticies.size(); i++) {
		p.addPoint(verticies[i].scale(f));
	}
	return p;
}

Vertex Polygon::center() {
	Vertex sum = verticies[0].add(verticies[1]).add(verticies[2]);
	return sum.scale(1.0f/3.0f);
}

bool Polygon::intersect(Ray ray) {
	// check the math at http://goo.gl/lwNn3
	
	Vertex v0 = verticies[0];
	Vertex u = verticies[1].sub(v0);
	Vertex v = verticies[2].sub(v0);
	Vertex n = u.cross(v);
	
	Vertex org = ray.getOrigin();
	Vertex dir = ray.getDirection();
		
	// see where ray hits polygon plane
	float a = n.dot(v0.sub(org));
	float b = n.dot(dir);
	if (fabs(b) < 0.00000001) {
		if (a == 0)
			return true; // ray is on plane
		else return false; // ray is paralle to plane
	}
	float r = a / b;
	if (r < 0)
		return 0; // ray points away from polygon
	Vertex intersect = org.add(dir.scale(r));
	
	// see if the intersection is in boundaries
	float uv, uu, vv, wv, wu;
	float s, t, d;
	Vertex w = intersect.sub(org);
	uv = u.dot(v);
	uu = u.dot(u);
	vv = v.dot(v);
	wv = w.dot(v);
	wu = w.dot(u);
	d = pow(uv, 2) - uu * vv;
	s = (uv * wv - vv * wu) / d;
	t = (uv * wu - uu * wv) / d;
	if (s < 0 || s > 1) return false;
	if (t < 0 || s+t > 1) return false;

	return true;
}
