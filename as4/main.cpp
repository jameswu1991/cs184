#include <vector>
#include <iostream>
#include "FreeImage.h"

#include <math.h>

#include "window.h"
#include "parser.h"
#include "rendering.h"

#include "vertex.h"
#include "polygon.h"
#include "sphere.h"
#include "model.h"
#include "scene.h"

#define WIDTH 250
#define HEIGHT 100
#define BPP 24

using namespace std;

Rendering rendering;
Parser parser;
Scene scene;
bool writeToFile = false;
char* filename;
int size = 640;

Rendering parseArgs(int argc, char** argv) {
	for (int i=0; i<argc; i++) {
		string s (argv[i]);
		if (s.compare("-reflect") == 0)
			rendering.reflectConst = atof(argv[i+1]);
		if (s.compare("-numReflections") == 0)
			rendering.numReflectsConst = atoi(argv[i+1]);
		if (s.compare("-ambient") == 0)
			rendering.ambientConst = atof(argv[i+1]);
		if (s.compare("-specular") == 0)
			rendering.specularConst = atof(argv[i+1]);
		if (s.compare("-pl") == 0)
			scene.addPointLight(
				atof(argv[i+1]),
				atof(argv[i+2]),
				atof(argv[i+3]),
				atof(argv[i+4]),
				atof(argv[i+5]),
				atof(argv[i+6]));
		if (s.compare("-dl") == 0)
			scene.addDirectionalLight(
				atof(argv[i+1]),
				atof(argv[i+2]),
				atof(argv[i+3]),
				atof(argv[i+4]),
				atof(argv[i+5]),
				atof(argv[i+6]));
		if (s.compare("-rotate") == 0)
			scene.rotate(
				atof(argv[i+1]),
				atof(argv[i+2]),
				atof(argv[i+3]));
		if (s.compare("-scale") == 0)
			scene.scale(
				atof(argv[i+1]),
				atof(argv[i+2]),
				atof(argv[i+3]));
		if (s.compare("-translate") == 0)
			scene.translate(
				atof(argv[i+1]),
				atof(argv[i+2]),
				atof(argv[i+3]));
		if (s.compare("-sphere") == 0)
			scene.addSphere(
				Sphere(Vertex(
					atof(argv[i+1]),
					atof(argv[i+2]),
					atof(argv[i+3])),
				atof(argv[i+4])));
		if (s.compare("-file") == 0)
			scene.addModel(parser.loadFile(argv[i+1]));
		if (s.compare("-width") == 0)
			size = atoi(argv[i+1]);
		if (s.compare("-output") == 0) {
			writeToFile = true;
			filename = argv[i+1];
		}	
	}
}

int main(int argc, char *argv[]) {
	parseArgs(argc, argv);
	Window *window = Window::get();
	window->initialize(argc, argv, size, size);
	
	rendering.render(scene, window);
	if (writeToFile) {
		window->saveFile(filename);
	}
	else window->show();
	
	return 0;
}


