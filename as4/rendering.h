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
	vector<Vertex> getImagePlane(Window* w);
	float raytrace(Ray ray, Scene scene);
public:
	void render(Scene s, Window* w);
};

#endif