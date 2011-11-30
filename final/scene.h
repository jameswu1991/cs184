#ifndef scene_h
#define scene_h

#include <vector>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "patch.h"

using namespace std;
using namespace Eigen;

class Scene {
public:
	vector<Patch> patches;
public:
	Scene ();
};

#endif