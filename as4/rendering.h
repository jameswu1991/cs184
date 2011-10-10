#ifndef rendering_h
#define rendering_h

#include <vector>
#include <math.h>

#include "window.h"
#include "vertex.h"
#include "polygon.h"
#include "sphere.h"
#include "model.h"
#include "scene.h"
#include "ray.h"

using namespace std;

class Rendering {
private:
	vector<vector<Vertex> > getImagePlane(Window* w, float z);
	float shade(Ray intersect, Scene scene);
	float reflect(Ray intersection, Vertex incomingLight, Scene scene, int numReflections);
public:
	float raytrace(Ray ray, Scene scene, int numReflections);
	void render(Scene s, Window* w);
};

#endif
