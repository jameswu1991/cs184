#include <vector>
#include <iostream>
#include <math.h>
#include <Eigen/Core>

#define WIDTH 400
#define HEIGHT 400

#include "parser.h"

using namespace std;

Parser parser;

int main(int argc, char *argv[]) {
	vector<Patch> patches = parser.loadFile(argv[1]);
	for (int a=0; a<patches.size(); a++) {
		patches[a].print();
	}
}