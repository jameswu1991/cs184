#include "scene.h"

void Scene::addModel(Model* m) {
	models.push_back(m);
}

void Scene::addSphere(Sphere sphere) {
	spheres.push_back(sphere);
}

void Scene::addPointLight(float x, float y, float z, float r, float g, float b) {
	Vertex l (x, y, z, r, g, b);
	pointLights.push_back(l);
}

void Scene::addDirectionalLight(float x, float y, float z, float r, float g, float b) {
	Vertex l (x, y, z, r, g, b);
	directionalLights.push_back(l);
}

void Scene::rotate(float x, float y, float z) {
	for (int a=0; a<models.size(); a++)
		models[a]->rotate(Vertex(x,y,z));
}

void Scene::scale(float x, float y, float z) {
	for (int a=0; a<models.size(); a++)
		models[a]->scale(x,y,z);
}

void Scene::translate(float x, float y, float z) {
	for (int a=0; a<models.size(); a++)
		models[a]->translate(x,y,z);
}

vector<Model*> Scene::getModels() {
	return models;
}

vector<Sphere> Scene::getSpheres() {
	return spheres;
}

vector<Vertex> Scene::getPointLights() {
	return pointLights;
}

vector<Vertex> Scene::getDirectionalLights() {
	return directionalLights;
}
