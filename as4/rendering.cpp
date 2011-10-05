#include "rendering.h"
#include <sys/time.h>

void Rendering::render(Scene scene, Window* window) {
	Vertex eye (0, 0, -7);
	vector<Vertex> screen = getImagePlane(window);
	
	timeval time;
	gettimeofday(&time, NULL);
	long millis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	
	for (int a=0; a<screen.size(); a++) {
		if (a%(screen.size()/1000) == 0)
			cout << (float)a/screen.size()*100 << "\%" << endl;
			// cout << "rendering " << a << "/" << screen.size() << "\n";
		
		Vertex pixel = screen[a];
		int x = pixel.get(0);
		int y = pixel.get(1);
		
		Vertex normPixel (
			((float)pixel.get(0) - 200)/100, 
			((float)pixel.get(1) - 200)/100, 
			pixel.get(2));
		
		Ray ray (eye, normPixel);
		float shade = raytrace(ray, scene);
		window->pixel(x, y, shade, shade, shade);
	}
	
	gettimeofday(&time, NULL);
	millis = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - millis;
	cout << millis << " milliseconds taken" << endl;
}

float Rendering::raytrace(Ray ray, Scene scene) {
	vector<Model*> models = scene.getModels();
	vector<Sphere> spheres = scene.getSpheres();
	for (int a=0; a<models.size(); a++) {
		Vertex normal = models[a]->intersect(ray);
		if (!normal.isNull()) {
			// normal.reflect(ray.direction())
			float shade = normal.dot(Vertex(1,1,1));
			if (shade < 0) shade = -shade;
			return shade;
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
			Vertex pixel (x, y, -5);
			screen.push_back(pixel);
		}
	}
	return screen;
}
