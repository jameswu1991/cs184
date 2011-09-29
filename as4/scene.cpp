#include "scene.h"

void Scene::addModel(Model* m) {
	models.push_back(m);
}

void Scene::addPointLight(float x, float y, float z) {
	Vertex l (x, y, z);
	pointLights.push_back(l);
}

void Scene::addDirectionalLight(float x, float y, float z) {
	Vertex l (x, y, z);
	directionalLights.push_back(l);
}

vector<Model*> Scene::getModels() {
	return models;
}

vector<Vertex> Scene::getPointLights() {
	return pointLights;
}

vector<Vertex> Scene::getDirectionalLights() {
	return directionalLights;
}