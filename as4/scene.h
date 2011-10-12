#ifndef scene_h
#define scene_h

#include "model.h"
#include "sphere.h"
#include "vertex.h"

using namespace std;

class Scene {
	vector<Model*> models;
	vector<Sphere> spheres;
	vector<Vertex> pointLights;
	vector<Vertex> directionalLights;
public:
	void addModel(Model* m);
	void addSphere(Sphere s);
	void addPointLight(float x, float y, float z, float r, float g, float b);
	void addDirectionalLight(float x, float y, float z, float r, float g, float b);
	vector<Model*> getModels();
	vector<Sphere> getSpheres();
	vector<Vertex> getPointLights();
	vector<Vertex> getDirectionalLights();
};

#endif
