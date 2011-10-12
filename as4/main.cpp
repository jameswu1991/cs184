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
	// scene.addDirectionalLight(-0.5, -1, 0);
	scene.addDirectionalLight(-0.1, -0.1, 0.1);
	
	// Model* m = parser.loadFile(argv[1]);
	// scene.addModel(m);
	scene.addSphere(Sphere(Vertex(0, 0, 0), 0.5));
	scene.addSphere(Sphere(Vertex(1, 0, 0), 0.5));
	// scene.addPointLight(0.2,0.4,0);
	
	rendering.render(scene, window);
	window->show();
	
	/*
	FreeImage_Initialise();
	
	FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP);
	RGBQUAD color;
	
	if (!bitmap)
		exit (1);
	
	//Draws a gradient from blue to green;
	for (int i=0; i<WIDTH; i++) {
		for (int j=0; j<HEIGHT; j++) {
			color.rgbRed = 0;
			color.rgbGreen = (double) i / WIDTH * 255.0;
			color.rgbBlue = (double) j / HEIGHT * 255.0;
			FreeImage_SetPixelColor(bitmap, i, j, &color);
		}
	}
	
	if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
		cout << "Image_successfully_saved!" <<endl;
	
	FreeImage_DeInitialise(); 
	*/

/*
	Window *window = Window::get();
	window->initialize(argc, argv, 400, 400);
	
	Model* m = parser.loadFile(argv[1]);
	scene.addModel(m);
	scene.addDirectionalLight(-1, -1, -1);
	//scene.addDirectionalLight(-0.1, -0.1, 0.1);
	//Vertex center1 = Vertex(3,3,2);
	Sphere s1 = Sphere(Vertex(0, 0, 0), 0.5);
	//Sphere s2 = Sphere(Vertex(1, 0, 0), 0.5);
	//Ray result = s.intersect(test);
	//result.getOrigin().print();
	//result.getDirection().print();
	//scene.addSphere(s1);
	scene.addSphere(s1);
	//scene.addSphere(s2);
	//rendering.shade(result, scene);

	//scene.addSphere(s);
	//scene.addSphere(s1);
	rendering.render(scene, window);
	
	window->saveFile();
	window->show();
*/

/*
	Model* m = parser.loadFile(argv[1]);
	Ray ray (Vertex(0,0,-2), Vertex(0,0,-1));
	scene.addModel(m);
	rendering.raytrace(ray, scene, 1);
*/
	
	return 0;

}
