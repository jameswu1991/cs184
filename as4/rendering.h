#ifndef rendering_h
#define rendering_h

#include "FreeImage.h"
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
	vector<vector<Vertex> > getImagePlaneF(int width, int height, float z); 
	float raytrace(Ray ray, Scene scene);
public:
	float shade(Ray intersect, Scene scene);
	void render(Scene s, Window* w);
	void saveFile(Window* w, int BPP);
};

#endif