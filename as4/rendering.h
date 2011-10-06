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
	float raytrace(Ray ray, Scene scene);
public:
	float shade(Ray intersect, Scene scene);
	void render(Scene s, Window* w);
};

#endif