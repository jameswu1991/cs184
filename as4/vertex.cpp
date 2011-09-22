#include "vertex.h"

Vertex::Vertex (float x, float y, float z) {
	float r[] = {x, y, z};
	vector<float> v (&r[0], &r[3]);
	data = v;
}

Vertex::Vertex (float r[], int length) {
	vector<float> v (&r[0], &r[length]);
	data = v;
}

Vertex::Vertex (vector<float> _data) {
	data = _data;
}
	
Vertex Vertex::add(Vertex v) {
	vector<float> sum;
	if (v.data.size() != data.size())
		throw 1;
	for (int a=0; a<v.data.size(); a++) 
		sum.push_back(v.data[a] + data[a]);
	return Vertex(sum);
}

Vertex Vertex::sub(Vertex v) {
	vector<float> diff;
	if (v.data.size() != data.size())
		throw 1;
	for (int a=0; a<v.data.size(); a++) 
		diff.push_back(data[a] - v.data[a]);
	return Vertex(diff);
}

Vertex Vertex::mul(Vertex v) {
	vector<float> prod;
	if (v.data.size() != data.size())
		throw 1;
	for (int a=0; a<v.data.size(); a++) 
		prod.push_back(data[a] * v.data[a]);
	return Vertex(prod);
}

Vertex Vertex::scale(float f) {
	vector<float> prod;
	for (int a=0; a<data.size(); a++) 
		prod.push_back(data[a] * f);
	return Vertex(prod);
}

Vertex Vertex::normalize() {
	float mag = magnitude();
	return scale(1/mag);
}
	
float Vertex::dot(Vertex v) {
	return mul(v).sum();
}

float Vertex::sum() {
	float sum = 0;
	for (int a=0; a<data.size(); a++) 
		sum += data[a];
	return sum;
}

float Vertex::magnitude() {
	float mag = 0;
	for (int i=0; i<data.size(); i++)
		mag += pow(data[i], 2);
	return sqrt(mag);
}

void Vertex::print() {
	cout << "(";
	for (int a=0; a<data.size(); a++) {
		cout << data[a];
		if (a+1 < data.size()) {
			cout << ", ";
		}
	}
	cout << ")";
}

void Vertex::draw() {
	glVertex3f(data[0], data[1], data[2]);
}
