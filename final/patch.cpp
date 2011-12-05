#include "patch.h"

using namespace std;
using namespace Eigen;

#define pi 3.1415926535897932384626433832795

/*
public:
vector<Vector3f> vertices;
vector<float> color;
float reflectance;
float irradiance;
map<Patch, float> viewFactors;
*/

Patch::Patch(vector<Vector3f> _vertices, vector<float> _color, float _reflectance, float _irradiance){
	vertices = _vertices;
	color = _color;
	reflectance = _reflectance;
	irradiance = _irradiance;
}

bool Patch::intersects(Vector3f start, Vector3f end) {
	// code guided by softsurfer.com's ray-triangle implementation
	
	// patch's two sides and a normal
	Vector3f u = vertices[1] - vertices[0];
	Vector3f v = vertices[2] - vertices[0];
	Vector3f n = u.cross(v);
	
	Vector3f dir = end - start;
	Vector3f trans = start - vertices[0];
	float a = -n.dot(trans);
	float b = n.dot(dir);
	
	if (fabs(b) < 0.0001)
		return false; // ray and triangle parallel
	
	float r = a / b;
	if (r < 0)
		return 0; // ray points away from triangle
	if (r > 1)
		return 0; // intersection happens outside of the segment
	
	Vector3f intersection = start + r * dir;
	
	float uu = u.dot(u);
	float uv = u.dot(v);
	float vv = v.dot(v);
	Vector3f w = intersection - vertices[0];
	float wu = w.dot(u);
	float wv = w.dot(v);
	float D = uv * uv - uu * vv;
	
	float s, t;
	s = (uv * wv - vv * wu) / D;
	if (s < 0 || s > 1)
		return false;
	t = (uv * wu - uu * wv) / D;
	if (t < 0 || t > 1)
		return false;
	
	return true;
}

Vector3f Patch::getCenter() {
	Vector3f topMidpoint = (vertices[0] + vertices[1])/2;
	Vector3f bottomMidpoint = (vertices[2] + vertices[3])/2;	
	Vector3f center  = (topMidpoint+bottomMidpoint)/2;
	return center;
}

float Patch::formFactor(Patch p) {
	
	Vector3f center = getCenter();
	Vector3f p_center = p.getCenter();
	
	float S;
	S = distance(center, p_center);

	Vector3f p_side1 = p.vertices[1] - p.vertices[0];
	Vector3f p_side2 = p.vertices[2] - p.vertices[1];
	Vector3f n2 = calculateNormal(p_side1, p_side2);
	Vector3f p_dv = center - p_center;
	p_dv.normalize();
	float dA2 = p_side1.norm() * p_side2.norm();
	
	Vector3f side1 = vertices[1] - vertices[0];
	Vector3f side2 = vertices[2] - vertices[1];
	Vector3f n1 = calculateNormal(side1, side2);
	Vector3f dv = p_center - center;
	dv.normalize();
	float dA1 = side1.norm() * side2.norm();
	
	float differentialAngle = n2.dot(p_dv) * n1.dot(dv);
	// make sure differential angle is between 0 and 1
	if (differentialAngle < 0) {
		differentialAngle = fabs(differentialAngle);
	}	
	
	float viewFactor = differentialAngle/(pi * pow(S,2)) * dA2;
	
	return viewFactor;
	
}

float Patch::distance(Vector3f p1, Vector3f p2) {
	return sqrt(pow(p1[0]-p2[0],2)+pow(p1[1]-p2[1],2)+pow(p1[2]-p2[2],2));
}

Vector3f Patch::calculateNormal(Vector3f side1, Vector3f side2) {
	Vector3f normal = side1.cross(side2);
	normal.normalize();
	return normal;
}

// PierreBdR's formula
// http://stackoverflow.com/questions/240778/random-points-inside-a-polygon
Vector3f Patch::samplePoint() {
	Vector3f side1 = vertices[1]-vertices[0];
	Vector3f side2 = vertices[3]-vertices[0];
	float a = (float)rand()/(float)RAND_MAX;
	float b = (float)rand()/(float)RAND_MAX;
	Vector3f p = a*side1 + b*side2;
	Vector3f AP = vertices[0]+p;
	return AP;
}
