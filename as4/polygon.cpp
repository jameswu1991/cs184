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
	Vertex normal = basis1.cross(basis2).normalize();
	// keep the normals pointing towards the -z axis
	if (normal.get(2)>0)
		normal = normal.scale(-1);
	return normal;
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

float Polygon::intersect(Ray ray) {
	Vertex va = verticies[0];
	Vertex vb = verticies[1];
	Vertex vc = verticies[2];
	Vertex vd = ray.getDirection();
	Vertex ve = ray.getOrigin();
	
	float a = va.get(0) - vb.get(0);
	float b = va.get(1) - vb.get(1);
	float c = va.get(2) - vb.get(2);
	float d = va.get(0) - vc.get(0);
	float e = va.get(1) - vc.get(1);
	float f = va.get(2) - vc.get(2);
	float g = vd.get(0);
	float h = vd.get(1);
	float i = vd.get(2);
	float j = va.get(0) - ve.get(0);
	float k = va.get(1) - ve.get(1);
	float l = va.get(2) - ve.get(2);
	
	Vertex temp (e*i-h*f, g*f-d*i, d*h-e*g);
	Vertex temp2 (a*k-j*b, j*c-a*l, b*l-k*c);
	float M = temp.mul(Vertex(a, b, c)).sum();
	
	float t = -temp2.mul(Vertex(f, e, d)).sum() / M;
	// TODO: consider t < t0 || t > t1
	
	float gamma = temp2.mul(Vertex(i, h, g)).sum() / M;
	if (gamma < 0 || gamma > 1)
		return -1;
	
	float beta = temp.mul(Vertex(j, k, l)).sum() / M;
	if (beta < 0 || beta > 1 - gamma)
		return -1;
	
	return t;
}
