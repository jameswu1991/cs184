#include "rendering.h"
#include <iostream>
#include "FreeImage.h"
#include <sys/time.h>

using namespace std;

Rendering::Rendering() {
	reflectConst = 0.5;
	numReflectsConst = 1;
	ambientConst = 0.1;
	specularConst = 10;
}

long now() {
	// return current time in milliseconds
	timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void Rendering::render(Scene scene, Window* window) {
	Vertex eye (0, 0, -10);
	// get a 2d array of Vertexes, one for each pixel
	vector<vector<Vertex> > screen = getImagePlane(window, -1);
	int numPixels = window->getWidth() * window->getHeight();
	
	// start a timer to print out the time at the endintersect
	long start = now();
	
	// for each pixel on the screen, cast a screen and shade
	for (int x=0; x<screen.size(); x++) {
		cout << "rendering column " << x << "/" << screen.size() << "\n";
		for (int y=0; y<screen[x].size(); y++) {
			Ray ray (eye, screen[x][y]);
			Vertex shade = raytrace(ray, scene, numReflectsConst);
			window->pixel(x, y, shade.get(0), shade.get(1), shade.get(2));
		}
	}
	
	cout << now() - start << " total milliseconds taken" << endl;
}

Vertex Rendering::raytrace(Ray ray, Scene scene, int numReflections) {
	vector<Model*> models = scene.getModels();
	vector<Sphere> spheres = scene.getSpheres();
	
	//ray.getOrigin().print();
	//ray.getDirection().print();
	//cout << endl;
	
	float lowestT = 100000;
	Vertex color (0,0,0);
	
	// for every model, check if intersect. if so, shade it as the pixel's color
	for (int a=0; a<models.size(); a++) {
		Ray intersect = models[a]->intersect(ray);
		// if intersect, then shade
		if (!intersect.getDirection().isNull()) {
			float t = models[a]->intersect_t(ray);
			if (t < lowestT) {
				lowestT = t;
				color = Vertex(0,0,0);
				color = color.add(shade(intersect, scene, ray.getDirection()).scale(1-reflectConst));
				color = color.add(reflect(intersect, ray.getDirection(), scene, numReflections).scale(reflectConst));
				color = color.add(Vertex(ambientConst,ambientConst,ambientConst));
			}
		}
	}
	
	for (int a=0; a<spheres.size(); a++) {
		Ray intersect = spheres[a].intersect(ray);
		if (!intersect.getDirection().isNull()) {
			float t = spheres[a].intersect_t(ray);
			if (t < lowestT) {
				lowestT = t;
				color = Vertex(0,0,0);
				color = color.add(shade(intersect, scene, ray.getDirection()).scale(1-reflectConst));
				color = color.add(reflect(intersect, ray.getDirection(), scene, numReflections).scale(reflectConst));
				color = color.add(Vertex(ambientConst,ambientConst,ambientConst));
			}
		}
	}
	return color;
}

Vertex Rendering::shade(Ray intersect, Scene scene, Vertex viewerDirection) {
	// intersect is a ray with origin at the point of intersect,
	// and direction of the normal of the intersected polygon
	Vertex shade (0,0,0);
	
	vector<Vertex> lights = scene.getDirectionalLights();
	for (int a=0; a<lights.size(); a++) {
		// see if that light is blocked, if so, it's shadow
		Vertex light = Vertex(lights[a].get(0), lights[a].get(1), lights[a].get(2));
		Vertex color = Vertex(lights[a].get(3), lights[a].get(4), lights[a].get(5));
		light = light.scale(-1);
		if (!isShadowed(intersect.getOrigin(), light, scene, false)) {
			light = light.normalize();
			float gradient = max(0.0f, light.dot(intersect.getDirection()));
			float specular = intersect.getDirection().reflect(light.scale(-1)).dot(viewerDirection.scale(-1).normalize());
			specular = pow(max(0.0f, specular),specularConst);
			shade = shade.add(color.scale(gradient+specular));
		}
	}
	
	vector<Vertex> plights = scene.getPointLights();
	for (int a=0; a<plights.size(); a++) {
		Vertex light = Vertex(plights[a].get(0), plights[a].get(1), plights[a].get(2));
		Vertex color = Vertex(plights[a].get(3), plights[a].get(4), plights[a].get(5));
		light = light.sub(intersect.getOrigin());
		if (!isShadowed(intersect.getOrigin(), light, scene, true)) {
			light = light.normalize();
			float gradient = max(0.0f, light.dot(intersect.getDirection()));
			float specular = intersect.getDirection().reflect(light.scale(-1)).dot(viewerDirection.scale(-1).normalize());
			specular = pow(max(0.0f, specular),10);
			shade = shade.add(color.scale(gradient+specular));
		}
	}
	return shade;
}

bool Rendering::isShadowed(Vertex surfaceIntersect, Vertex lightDirection, Scene scene, bool isPointSource) {
	vector<Model*> models = scene.getModels();
	vector<Sphere> spheres = scene.getSpheres();
	for (int modelIndex=0; modelIndex<models.size(); modelIndex++) {
		// create a ray starting from point of intersect and going in the direction of light
		Ray shadowTracer;
		shadowTracer.setOrigin(surfaceIntersect);
		shadowTracer.setDirection(lightDirection);
		
		// if the ray hits something
		float t = models[modelIndex]->intersect_t(shadowTracer);
		if (t > 0) {
			// if it's a directional source, then it is being shadowed
			if (!isPointSource)
				return true;
			// if it's a point light source and intersection is in front of point source, then it is being shadowed
			else if (t < 1)
				return true;
		}
	}
	for (int sphereIndex=0; sphereIndex<spheres.size(); sphereIndex++) {
		Ray shadowDetector;
		shadowDetector.setOrigin(surfaceIntersect);
		shadowDetector.setDirection(lightDirection);
		
		float t = spheres[sphereIndex].intersect_t(shadowDetector);
		if (t > 0) {
			if (!isPointSource)
				return true;
			else if (t < 1)
				return true;
		}
	}
		
	return false;
}

Vertex Rendering::reflect(Ray intersection, Vertex incomingLight, Scene scene, int numReflections) {
	// trace a line from point of intersection out with direction of the reflection off of the normal
	if (numReflections == 0)
		return Vertex(0,0,0);
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


