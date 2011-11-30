#include <Eigen/Geometry>

#include "window.h"
#include "scene.h"

using namespace std;
using namespace Eigen;

Scene scene;
Window window(scene);

bool adaptive = false;

int main(int argc, char *argv[]) {
	window.show(argc, argv);
}

