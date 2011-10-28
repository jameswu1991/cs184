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
	
	window.show(argc, argv);
}

