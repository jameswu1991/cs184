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
	void subdivide();
	void subdivideTo16();
	Vector3f midpoint(Vector3f p1, Vector3f p2);
};

#endif