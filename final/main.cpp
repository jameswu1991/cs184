#include <Eigen/Geometry>

#include "parser.h"
#include "window.h"

using namespace std;
using namespace Eigen;

Parser parser;
Window window;

bool adaptive = false;

int main(int argc, char *argv[]) {
	vector<Patch> patches = parser.loadFile(argv[1]);
	
	/* MatrixXf front (6, 3);
	        front << -1.5f, -1.0f, 1.5f,
	                1.5f, -1.0f, 1.5f,
	                1.5f, 1.0f, 1.5f,
	                -1.5f, 1.0f, 1.5f,
	                -1.0f, 0.0f, 1.0f,
					1.0f, 0.0f, 1.0f;
	window.addTriangle(front.transpose());
	*/
	
	float step = atof(argv[2]);
	for (int i=0; i<argc; i++) {
		string s (argv[i]);
		if (s.compare("-a") == 0) {
			adaptive = true;
		}
	}
	if (adaptive == true) {		
		for (int a=0; a<patches.size(); a++) {
			patches[a].tessellate(step);
			vector<MatrixXf> triangles =  patches[a].triangles;
			for (int i=0; i<triangles.size(); i++) {
				window.addTriangle(triangles[i]);
			}
		}	
	}
	else {
		for (int a=0; a<patches.size(); a++) {
			patches[a].subdividepatch(step);
			vector<MatrixXf> quadrilaterals =  patches[a].quads;
			for (int i=0; i<quadrilaterals.size(); i++) {
				window.addQuad(quadrilaterals[i]);
			}
		}
	}
	
	window.show(argc, argv);
}

