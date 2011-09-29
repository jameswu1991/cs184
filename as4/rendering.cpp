#include "rendering.h"

void Rendering::render(Scene scene, Window* window) {
	Vertex eye (0, 0, -5);
	vector<Vertex> screen = getImagePlane(window);
	
	for (int a=0; a<screen.size(); a++) {
		if (a%10 == 0)
			cout << "rendering " << a << "/" << screen.size() << "\n";
		
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
}

float Rendering::raytrace(Ray ray, Scene scene) {
	vector<Model*> models = scene.getModels();
	for (int a=0; a<models.size(); a++) {
		if (models[a]->intersect(ray)) {
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
