#include "rendering.h"
#include <sys/time.h>

long now() {
	timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void Rendering::render(Scene scene, Window* window) {
	Vertex eye (0, 0, -2);
	vector<vector<Vertex> > screen = getImagePlane(window, -1);
	int numPixels = window->getWidth() * window->getHeight();
	
	long start = now();
	
	
	for (int x=0; x<screen.size(); x++) {
		cout << "rendering column " << x << "/" << screen.size() << "\r";
		for (int y=0; y<screen[x].size(); y++) {
			Ray ray (eye, screen[x][y]);
			float shade = raytrace(ray, scene);
			window->pixel(x, y, shade, shade, shade);
		}
	}
	
	cout << now() - start << " total milliseconds taken" << endl;
}

float Rendering::raytrace(Ray ray, Scene scene) {
	vector<Model*> models = scene.getModels();
	vector<Sphere> spheres = scene.getSpheres();
	for (int a=0; a<models.size(); a++) {
		Ray intersect = models[a]->intersect(ray);
		// if intersect, then shade
		if (!intersect.getDirection().isNull()) {
			return shade(intersect, scene) + 0.1;
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

float Rendering::shade(Ray intersect, Scene scene) {
	float shade = 0;
	Vertex surface = intersect.getOrigin();
	Vertex normal = intersect.getDirection();
	vector<Model*> models = scene.getModels();
	
	vector<Vertex> lights = scene.getDirectionalLights();
	for (int a=0; a<lights.size(); a++) {
		Vertex light = lights[a].scale(-1);
		float change = light.dot(normal);
		for (int a=0; a<models.size(); a++) {
			Ray shadowDetector = Ray(Vertex(0,0,0),Vertex(0,0,0));
			float floatInaccuracyConst = 0.0001;
			shadowDetector.setOrigin(
				intersect.getOrigin().add(intersect.getDirection().scale(floatInaccuracyConst)));
			shadowDetector.setDirection(light);
			if (models[a]->intersect_b(shadowDetector)) {
				change = 0;
			}
		}
		shade += max(0.0f, change);
	}
	
	return shade;
}

vector<vector<Vertex> > Rendering::getImagePlane(Window* window, float z) {
	int width = window->getWidth();
	int height = window->getHeight();
	float xcenter = width/2;
	float ycenter = height/2;
	vector<vector<Vertex> > screen (width, vector<Vertex>(height));
	for (int x=0; x<width; x++)
		for (int y=0; y<height; y++){
			screen[x][y] = Vertex(
				(x - xcenter) / xcenter,
				(y - ycenter) / ycenter,
				z);
		}
	return screen;
}
