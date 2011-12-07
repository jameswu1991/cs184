#ifndef scene_h
#define scene_h

#include <vector>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "patch.h"

#include "patch.h"

using namespace std;
using namespace Eigen;

class Scene {
public:
	vector<Patch> patches;
public:
	Scene ();
	float visibility(int p1idx, int p2idx);
	void calcFormFactors();
	void subdivide();
	void subdivideNTimes(int n);
	void divide(int width);
	Vector3f midpoint(Vector3f p1, Vector3f p2);
};

#endif