#include <vector>
#include <iostream>
#include <math.h>

#include "window.h"
#include "parser.h"
#include "rendering.h"

#include "vertex.h"
#include "polygon.h"
#include "sphere.h"
#include "model.h"
#include "scene.h"

Parser parser;
Rendering rendering;
Scene scene;

int main(int argc, char *argv[]) {
	Window *window = Window::get();
	window->initialize(argc, argv);
	
	Model* m = parser.loadFile(argv[1]);
	scene.addModel(m);
	scene.addDirectionalLight(-1, -0.2, 0);
	// Vertex center = Vertex(0, 0, 0);
	// Sphere s = Sphere(center, 0.5);
	// 	scene.addSphere(s);
	rendering.render(scene, window);
	
	window->show();
	return 0;
}
