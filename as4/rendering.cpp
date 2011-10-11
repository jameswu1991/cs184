#include "rendering.h"
#include <iostream>
#include "FreeImage.h"
#include <sys/time.h>

using namespace std;

long now() {
	// return current time in milliseconds
	timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void Rendering::render(Scene scene, Window* window) {
	Vertex eye (0, 0, -2);
	// get a 2d array of Vertexes, one for each pixel
	vector<vector<Vertex> > screen = getImagePlane(window, -1);
	int numPixels = window->getWidth() * window->getHeight();
	
	// start a timer to print out the time at the end
	long start = now();
	
	// for each pixel on the screen, cast a screen and shade
	for (int x=0; x<screen.size(); x++) {
		cout << "rendering column " << x << "/" << screen.size() << "\r";
		for (int y=0; y<screen[x].size(); y++) {
			Ray ray (eye, screen[x][y]);
			float shade = raytrace(ray, scene, 1);
			window->pixel(x, y, shade, shade, shade);
		}
	}
	
	cout << now() - start << " total milliseconds taken" << endl;
}

float Rendering::raytrace(Ray ray, Scene scene, int numReflections) {
	vector<Model*> models = scene.getModels();
	vector<Sphere> spheres = scene.getSpheres();
	
	// for every model, check if intersect. if so, shade it as the pixel's color
	for (int a=0; a<models.size(); a++) {
		Ray intersect = models[a]->intersect(ray);
		// if intersect, then shade
		if (!intersect.getDirection().isNull()) {
			float color = 0;
			// some of the color is from the shade of the object
			color += 0.5 * shade(intersect, scene);
			// some of the color is from the reflection of the object
			color += 0.5 * reflect(intersect, ray.getDirection(), scene, numReflections);
			color += 0.1;
			return color;
		}
	}
	for (int a=0; a<spheres.size(); a++) {
		Ray intersect = spheres[a].intersect(ray);
		if (!intersect.getDirection().isNull()) {
			float color = 0;
			printf("Inside spheres code\n");
			// some of the color is from the shade of the object
			color += 0.5 * shade(intersect, scene);
			color += 0.1;
			printf("Color is %f\n", color);
			return color;
		}
	}
	return 0;
}

float Rendering::shade(Ray intersect, Scene scene) {
	// intersect is a ray with origin at the point of intersect,
	// and direction of the normal of the intersected polygon
	float shade = 0;
	vector<Model*> models = scene.getModels();
	vector<Sphere> spheres = scene.getSpheres();
	
	// for every light, calculate the shadow contribution
	vector<Vertex> lights = scene.getDirectionalLights();
	for (int a=0; a<lights.size(); a++) {
		Vertex light = lights[a].scale(-1);
		float change = light.dot(intersect.getDirection());
		// see if that light is blocked, if so, it's shadow
		for (int a=0; a<models.size(); a++) {
			Ray shadowDetector = Ray(Vertex(0,0,0),Vertex(0,0,0));
			float floatInaccuracyConst = 0.0001; // to prevent self-shadowing
			shadowDetector.setOrigin(intersect.getOrigin());
			shadowDetector.setDirection(light);
			// intersect_b() is the same as intersect(), except returns a boolean
			if (models[a]->intersect_b(shadowDetector)) {
				// if light is blocked, shadow the contribution
				change = 0;
			}
		}
		for (int b=0; b<spheres.size(); b++) {
			Ray shadowDetector = Ray(Vertex(0,0,0),Vertex(0,0,0));
			float floatInaccuracyConst = 0.0001; // to prevent self-shadowing
			shadowDetector.setOrigin(intersect.getOrigin());
			shadowDetector.setDirection(light);
			// intersect_b() is the same as intersect(), except returns a boolean
			if (spheres[b].intersect_b(shadowDetector)) {
				// if light is blocked, shadow the contribution
				change += 0;
			}
		}
		shade += max(0.0f, change);
	}
	
	return shade;
}

float Rendering::reflect(Ray intersection, Vertex incomingLight, Scene scene, int numReflections) {
	// trace a line from point of intersection out with direction of the reflection off of the normal
	if (numReflections == 0)
		return 0;
	Vertex direction = intersection.getDirection().reflect(incomingLight);
	Vertex origin = intersection.getOrigin();
	Ray reflectionRay;
	reflectionRay.setOrigin(origin);
	reflectionRay.setDirection(direction);
	// return the color of that ray
	return raytrace(reflectionRay, scene, numReflections-1);
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


