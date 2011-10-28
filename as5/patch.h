#ifndef patch_h
#define patch_h

#include <vector>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

class Patch {
public:
	vector<Vector3f> points;
	vector<Vector3f> sdPoints;
	vector<Vector3f> sdNormals;
	vector<MatrixXf> quads;
public:
	Patch (vector<Vector3f> points);
	void print();
	vector<Vector3f> bezcurveinterp(vector<Vector3f> curve, float u);
	vector<Vector3f> bezpatchinterp(float u, float v);
	void subdividepatch(float step);
	vector<vector<Vector3f> > controlForV();
	vector<vector<Vector3f> > controlForU();
};

#endif