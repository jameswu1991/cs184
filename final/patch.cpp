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
	Vector3f p_dv = p_center - center;
	float theta2 = acos(n2.dot(p_dv)/(n2.norm() * p_dv.norm()));
	float dA2 = p_side1.norm() * p_side2.norm();
	
	Vector3f side1 = vertices[1] - vertices[0];
	Vector3f side2 = vertices[2] - vertices[1];
	Vector3f n1 = calculateNormal(side1, side2);
	Vector3f dv = center - p_center;
	float theta1 = acos(n1.dot(dv)/(n1.norm() * dv.norm()));
	float dA1 = side1.norm() * side2.norm();	
	
	float viewFactor = ((cos(theta1)*cos(theta2))/(pi * pow(S,2))) * dA2;
	
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
