#ifndef patch_h
#define patch_h

#include <vector>
#include <iostream>
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <map>

using namespace std;
using namespace Eigen;

class Patch {
public:
	vector<Vector3f> vertices;
	vector<float> color;
	float reflectance;
	float irradiance;
	map<int, float> viewFactors;
public:
	Patch(vector<Vector3f> _vertices, vector<float> _color, float _reflectance, float _irradiance);
	float formFactor(Patch p);
	Vector3f getCenter();
	float distance(Vector3f p1, Vector3f p2);
	Vector3f calculateNormal(Vector3f side1, Vector3f side2);
};

#endif