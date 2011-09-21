#include "v_math.h"

vector<float> getVector(float x, float y, float z) {
	float r[] = {x, y, z};
	vector<float> v (&r[0], &r[3]);
	return v;
}

vector<float> getVector(float r[], int length) {
	vector<float> v (&r[0], &r[length]);
	return v;
}

void v_print(vector<float> a) {
	for(int i=0; i<a.size(); ++i)
		cout << a[i] << " ";
	cout << endl;
}

float getZ(float x, float y, float radius) {
	float z = sqrt(pow(radius, 2) - pow(x, 2) - pow(y, 2));
	if (z != z) return 0; // if z is NaN
	return z;
}

vector<float> v_scale(vector<float> v, float s) {
	for (int a=0; a<v.size(); a++) 
		v[a] *= s;
	return v;
}

vector<float> v_add(vector<float> v, vector<float> w) {
	if (v.size() != w.size())
		throw 1;
	for (int a=0; a<v.size(); a++) 
		v[a] += w[a];
	return v;
}

vector<float> v_sub(vector<float> v, vector<float> w) {
	if (v.size() != w.size())
		throw 1;
	for (int a=0; a<v.size(); a++) 
		v[a] -= w[a];
	return v;
}

vector<float> v_mul(vector<float> v, vector<float> w) {
	if (v.size() != w.size())
		throw 1;
	for (int a=0; a<v.size(); a++) 
		v[a] *= w[a];
	return v;
}

float v_sum(vector<float> v) {
	float sum = 0;
	for (int i=0; i<v.size(); i++)
		sum += v[i];
	return sum;
}

float dot(vector<float> x, vector<float> y) {
	if (x.size() != y.size())
		throw 1;
	float sum = 0;
	for (int i=0; i<x.size(); i++)
		sum += x[i] * y[i];
	return sum;
}

vector<float> reflection(vector<float> light, vector<float> surface_normal) {
	return v_sub(v_scale(surface_normal, dot(light, surface_normal)*2), light);
}

float magnitude(vector<float> v) {
	float mag = 0;
	for (int i=0; i<v.size(); i++)
		mag += pow(v[i], 2);
	return sqrt(mag);
}

vector<float> normalize(vector<float> v) {
	float mag = magnitude(v);
	for (int i=0; i<v.size(); i++) 
		v[i] /= mag;
	return v;
}