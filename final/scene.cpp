#include "scene.h"

using namespace Eigen;
using namespace std;

Scene::Scene() {
	
}

void Scene::subdivideTo16() {
	Scene::subdivide();
	Scene::subdivide();
	Scene::subdivide();
}

void Scene::subdivide() {
	vector<Patch> newPatches;
	int i;
	for (i=0; i<patches.size(); i++) {
		// Get the vertices of the current patch
		vector<float> origColor = patches[i].color;
		float origRefl = patches[i].reflectance;
		float origIrr = patches[i].irradiance;
		Vector3f topLeft = patches[i].vertices[0];
		Vector3f topRight = patches[i].vertices[1];
		Vector3f bottomRight = patches[i].vertices[2];
		Vector3f bottomLeft = patches[i].vertices[3];
		Vector3f topMidpoint = midpoint(topLeft, topRight);
		Vector3f rightMidpoint = midpoint(topRight, bottomRight);
		Vector3f bottomMidpoint = midpoint(bottomLeft, bottomRight);
		Vector3f leftMidpoint = midpoint(topLeft, bottomLeft);
		Vector3f center = midpoint(topMidpoint,bottomMidpoint);
		
		// Calculate the new vertices after subdivision
		vector<Vector3f> newTopLeftV;
		vector<Vector3f> newTopRightV;
		vector<Vector3f> newBottomRightV;
		vector<Vector3f> newBottomLeftV;
		
		newTopLeftV.push_back(topLeft);
		newTopLeftV.push_back(topMidpoint);
		newTopLeftV.push_back(center);
		newTopLeftV.push_back(leftMidpoint);
		
		newTopRightV.push_back(topMidpoint);
		newTopRightV.push_back(topRight);
		newTopRightV.push_back(rightMidpoint);
		newTopRightV.push_back(center);
		
		newBottomRightV.push_back(center);
		newBottomRightV.push_back(rightMidpoint);
		newBottomRightV.push_back(bottomRight);
		newBottomRightV.push_back(bottomMidpoint);
		
		newBottomLeftV.push_back(leftMidpoint);
		newBottomLeftV.push_back(center);
		newBottomLeftV.push_back(bottomMidpoint);
		newBottomLeftV.push_back(bottomLeft);
		
		// Store the vertices for the new patches
		Patch topLeftPatch = Patch(newTopLeftV, origColor, origRefl, origIrr);
		Patch topRightPatch = Patch(newTopRightV, origColor, origRefl, origIrr);
		Patch bottomRightPatch = Patch(newBottomRightV, origColor, origRefl, origIrr);
		Patch bottomLeftPatch = Patch(newBottomLeftV, origColor, origRefl, origIrr);
		
		newPatches.push_back(topLeftPatch);
		newPatches.push_back(topRightPatch);
		newPatches.push_back(bottomRightPatch);
		newPatches.push_back(bottomLeftPatch);
	}
	patches = newPatches;
}

Vector3f Scene::midpoint(Vector3f p1, Vector3f p2) {
	Vector3f midpoint((p1[0]+p2[0])/2, (p1[1]+p2[1])/2, (p1[2]+p2[2])/2);
	return midpoint;
}