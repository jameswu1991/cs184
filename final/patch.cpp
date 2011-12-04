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

bool Patch::intersects(Vertex3f start, Vertex3f end) {
	// code guided by softsurfer.com's ray-triangle implementation
	
	// patch's two sides and a normal
	Vector3f u = vertices[1] - vertices[0];
	Vector3f v = vertices[2] - vertices[0];
	Vector3f v = u.cross(v);
	
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
	
	Vertex3f intersection = start + r * dir;
	
	float uu = u.dot(u);
	float uv = u.dot(v);
	float vv = v.dot(v);
	Vertex3f w = intersection - vertices[0];
	float wu = w.dot(u);
	float wv = w.dot(v);
	float D = uv * uv - uu * vv;
	
	float s, t;
	s = (uv * wv - vv * wu) / D;
	if (s < 0.0 || s > 1.0)
		return false;
	t = (uv * wu - uu * wv) / D;
	if (t < 0.0 || t > 1.0)
		return false;
	
	return true;
}

float Patch::formFactor(Patch p) {
	
	// Calculate center for current patch
	Vector3f topLeft = vertices[0];
	Vector3f topRight = vertices[1];
	Vector3f bottomRight = vertices[2];
	Vector3f bottomLeft = vertices[3];
	Vector3f topMidpoint = midpoint(topLeft, topRight);
	Vector3f bottomMidpoint = midpoint(bottomLeft, bottomRight);
	Vector3f center = midpoint(topMidpoint,bottomMidpoint);
	
	// Calculate center for current patch
	Vector3f p_topLeft = p.vertices[0];
	Vector3f p_topRight = p.vertices[1];
	Vector3f p_bottomRight = p.vertices[2];
	Vector3f p_bottomLeft = p.vertices[3];
	Vector3f p_topMidpoint = midpoint(p_topLeft, p_topRight);
	Vector3f p_bottomMidpoint = midpoint(p_bottomLeft, p_bottomRight);
	Vector3f p_center = midpoint(p_topMidpoint, p_bottomMidpoint);
	
	float S;
	S = distance(center, p_center);

	Vector3f p_side1;
	Vector3f p_side2;
	p_side1 << p_topRight[0]- p_topLeft[0],
			   p_topRight[1]- p_topLeft[1],
			   p_topRight[2]- p_topLeft[2];
	p_side2 << p_bottomRight[0]- p_topRight[0],
			   p_bottomRight[1]- p_topRight[1],
			   p_bottomRight[2]- p_topRight[2];
	Vector3f n2 = calculateNormal(p_side1, p_side2);
	Vector3f p_dv = p_center - center;
	float theta2 = acos(n2.dot(p_dv)/(n2.norm() * p_dv.norm()));
	float dA2 = p_side1.norm() * p_side2.norm();
	
	Vector3f side1;
	Vector3f side2;
	side1 << topRight[0]- topLeft[0],
			 topRight[1]- topLeft[1],
			 topRight[2]- topLeft[2];
	side2 << bottomRight[0]- topRight[0],
			 bottomRight[1]- topRight[1],
			 bottomRight[2]- topRight[2];
	Vector3f n1 = calculateNormal(side1, side2);
	Vector3f dv = center - p_center;
	float theta1 = acos(n1.dot(dv)/(n1.norm() * dv.norm()));
	float dA1 = side1.norm() * side2.norm();	
	
	float viewFactor = ((cos(theta1)*cos(theta2))/(pi * pow(S,2))) * dA2;
	
	return viewFactor;
	
}

Vector3f Patch::midpoint(Vector3f p1, Vector3f p2) {
	Vector3f midpoint((p1[0]+p2[0])/2, (p1[1]+p2[1])/2, (p1[2]+p2[2])/2);
	return midpoint;
}

float Patch::distance(Vector3f p1, Vector3f p2) {
	return sqrt(pow(p1[0]-p2[0],2)+pow(p1[1]-p2[1],2)+pow(p1[2]-p2[2],2));
}

Vector3f Patch::calculateNormal(Vector3f side1, Vector3f side2) {
	float n_x = side1[1]*side2[2] - side1[2]*side2[1];
	float n_y = side1[2]*side2[0] - side1[0]*side2[2];
	float n_z = side1[0]*side2[1] - side1[1]*side2[0];
	Vector3f normal(n_x, n_y, n_z);
	normal.normalize();
	return normal;
}
