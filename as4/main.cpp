#include <vector>
#include <iostream>
#include <math.h>

#include "window.h"
#include "parser.h"
#include "rendering.h"

#include "vertex.h"
#include "polygon.h"
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
	rendering.render(scene, window);
	
	window->show();
	return 0;
}
