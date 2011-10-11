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

Parser parser;
Rendering rendering;
Scene scene;

int main(int argc, char *argv[]) {

	Window *window = Window::get();
	window->initialize(argc, argv, 400, 400);
	
	Model* m = parser.loadFile(argv[1]);
	m->rotate(Vertex(0.1, 0.1, 0.1));
	scene.addModel(m);
	scene.addDirectionalLight(-0.5, -1, 0);
	scene.addDirectionalLight(-0.1, -0.1, 0.1);
/*
	Vertex center = Vertex(0, 0, 1);
	Sphere s = Sphere(center, 0.1);
	scene.addSphere(s);
*/
	rendering.render(scene, window);
	
	window->saveFile();
	window->show();

	return 0;

}
