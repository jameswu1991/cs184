#ifndef patch_h
#define patch_h

#include <vector>
#include <iostream>
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <map>


#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

using namespace std;
using namespace Eigen;

class Patch {
public:
	vector<Vector3f> vertices;
	Vector3f reflectance;
	Vector3f irradiance;
	map<int, float> viewFactors;
public:
	Patch(vector<Vector3f> _vertices, Vector3f _reflectance, Vector3f _irradiance);
	bool intersects(Vector3f start, Vector3f end, Vector3f patchNormal);
	float formFactor(Patch p);
	Vector3f getCenter();
	float distance(Vector3f p1, Vector3f p2);
	Vector3f calculateNormal(Vector3f side1, Vector3f side2);
	Vector3f samplePoint();
	Vector3f normal();
};

#endif