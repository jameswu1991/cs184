#include <Eigen/Geometry>

#include "parser.h"
#include "window.h"

using namespace std;

Parser parser;
Window window;

int main(int argc, char *argv[]) {
	vector<Patch> patches = parser.loadFile(argv[1]);
	for (int a=0; a<patches.size(); a++) {
		patches[a].subdividepatch(0.1);
		// patches[a].quads;
	}
	
	
	MatrixXf front (8, 3);
	front << -1.5f, -1.0f, 1.5f,
		1.5f, -1.0f, 1.5f,
		1.5f, 1.0f, 1.5f,
		-1.5f, 1.0f, 1.5f,
		-1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		-1.0f, 0.0f, 1.0f;
	window.addQuad(front.transpose());

	MatrixXf right (8, 3);
	right << 1.5f, -1.0f, -1.5f,
		1.5f, 1.0f, -1.5f,
		1.5f, 1.0f, 1.5f,
		1.5f, -1.0f, 1.5f,
		1.0f, 0.0f, -1.0f,
		1.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f;
	window.addQuad(right.transpose());

	MatrixXf back (8, 3);
	back << -1.5f, -1.0f, -1.5f,
		-1.5f, 1.0f, -1.5f,
		1.5f, 1.0f, -1.5f,
		1.5f, -1.0f, -1.5f,
		-1.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, -1.0f,
		1.0f, 0.0f, -1.0f,
		1.0f, 0.0f, -1.0f;
	window.addQuad(back.transpose());

	MatrixXf left (8, 3);
	left << -1.5f, -1.0f, -1.5f,
		-1.5f, -1.0f, 1.5f,
		-1.5f, 1.0f, 1.5f,
		-1.5f, 1.0f, -1.5f,
		-1.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, 1.0f,
		-1.0f, 0.0f, 1.0f,
		-1.0f, 0.0f, -1.0f;
	window.addQuad(left.transpose());
	
	window.show(argc, argv);
}

