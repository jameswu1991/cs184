#include "patch.h"

Patch::Patch(vector<Eigen::MatrixXf> _points) {
	points = _points;
}

void Patch::evaluate(float u, float v) {
	
}

void Patch::print() {
	cout << "Patch" << endl;
	for (int a=0; a<4; a++) {
		for (int b=0; b<4; b++) {
			cout << "(";
			cout << points[a*4 + b](0, 0) << ", ";
			cout << points[a*4 + b](1, 0) << ", ";
			cout << points[a*4 + b](2, 0);
			cout << ") ";
		}
		cout << endl;
	}
	cout << endl;
}