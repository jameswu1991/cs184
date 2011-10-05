#include "rendering.h"
#include <sys/time.h>

void Rendering::render(Scene scene, Window* window) {
	Vertex eye (0, 0, -4);
	vector<Vertex> screen = getImagePlane(window);
	
	timeval time;
	gettimeofday(&time, NULL);
	long millis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	
	for (int a=0; a<screen.size(); a++) {
		
		// if (a%10 == 0)
		// 			cout << "rendering " << a << "/" << screen.size() << "\n";
		
		Vertex pixel = screen[a];
		int x = pixel.get(0);
		int y = pixel.get(1);
		
		Vertex normPixel (
			((float)pixel.get(0) - 200)/400, 
			((float)pixel.get(1) - 200)/400, 
			pixel.get(2));
		
		Ray ray (eye, normPixel);
		float shade = raytrace(ray, scene);
		window->pixel(x, y, shade, shade, shade);
	}
	
	gettimeofday(&time, NULL);
	millis = millis - ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

float Rendering::raytrace(Ray ray, Scene scene) {
	vector<Model*> models = scene.getModels();
	vector<Sphere> spheres = scene.getSpheres();
	for (int a=0; a<models.size(); a++) {
		if (models[a]->intersect(ray)) {
			return 1;
		}
	}
	for (int a=0; a<spheres.size(); a++) {
		vector<float> ts = spheres[a].intersect(ray);
		if (ts.size()!=0) {
			return 1;
		}
	}
	return 0;
}

vector<Vertex> Rendering::getImagePlane(Window* window) {
	vector<Vertex> screen;
	for (int x=0; x<window->getWidth(); x++) {
		for (int y=0; y<window->getHeight(); y++) {
			Vertex pixel (x, y, -3);
			screen.push_back(pixel);
		}
	}
	return screen;
}
