#include <Eigen/Geometry>

#include "parser.h"
#include "window.h"

using namespace std;
using namespace Eigen;

Parser parser;
Window window;

int main(int argc, char *argv[]) {
	vector<Patch> patches = parser.loadFile(argv[1]);
	patches[0].tessellate(0.1);
	/* for (int a=0; a<patches.size(); a++) {
		patches[a].subdividepatch(0.3);
		vector<MatrixXf> quadrilaterals =  patches[a].quads;
		for (int i=0; i<quadrilaterals.size(); i++) {
			window.addQuad(quadrilaterals[i]);
		}
	}
	window.show(argc, argv); */
}

