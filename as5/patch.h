#ifndef patch_h
#define patch_h

#include <vector>
#include <iostream>
#include <Eigen/Core>

using namespace std;

class Patch {
	vector<Eigen::MatrixXf> points;
public:
	Patch (vector<Eigen::MatrixXf> points);
	void evaluate(float u, float v);
};

#endif