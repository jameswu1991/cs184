#include "polygon.h"

void Polygon::addPoint(Vertex v) {
	verticies.push_back(v);
}

vector<Vertex> Polygon::getVerticies() {
	return verticies;
}

void Polygon::print() {
	for (int i=0; i<verticies.size(); i++) {
		cout << "[";
		verticies[i].print();
		cout << "]" << endl;
	}
}

void Polygon::draw() {
	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
	for (int i=0; i<verticies.size(); i++) {
		verticies[i].draw();
	}
	glEnd();
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