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
	map<Patch, float> viewFactors;
public:
	Patch(vector<Vector3f> vertices, vector<float> color, float reflectance, float irradiance, map<Patch, float> viewFactors);
};

#endif