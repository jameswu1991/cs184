#ifndef rendering_h
#define rendering_h

#include <vector>
#include <iostream>
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <map>
#include "patch.h"

using namespace Eigen;
using namespace std;

class Rendering {
public:
	Rendering ();
	float formFactor(Patch p1,Patch p2);
	float getNewIrradiance(float currentIrradiance, vector<Patch> otherPatches);
};

#endif