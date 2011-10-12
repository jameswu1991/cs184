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
	Vertex reflect(Ray intersection, Vertex incomingLight, Scene scene, int numReflections);
	Vertex raytrace(Ray ray, Scene scene, int numReflections);
	bool isShadowed(Vertex surfaceIntersect, Vertex lightDirection, Scene scene, bool isPointSource);
public:
	void render(Scene s, Window* w);
	Vertex shade(Ray intersect, Scene scene, Vertex viewerDirection);
	void saveFile(Window* w, int BPP);
};

#endif
