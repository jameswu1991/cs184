#include "scene.h"

using namespace Eigen;
using namespace std;

vector<float> getVector(float r, float g, float b) {
	float ar[] = {r, g, b};
	vector<float> v (&ar[0], &ar[3]);
	return v;
}

Scene::Scene() {
	vector<Vector3f> array(4);
	
	/*
	// test
	array[0]=Vector3f(0, 1, 0);
	array[1]=Vector3f(1, 1, 0);
	array[2]=Vector3f(1, 0, 0);
	array[3]=Vector3f(0, 0, 0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	*/
		
	// floor
	array[0]=Vector3f(552.8, 0, 0);
	array[1]=Vector3f(0, 0, 0);
	array[2]=Vector3f(0, 0, 559.2);
	array[3]=Vector3f(549.6, 0, 559.2);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	// light
	array[0]=Vector3f(343, 548.8, 227);
	array[1]=Vector3f(343, 548.8, 332);
	array[2]=Vector3f(213, 548.8, 332);
	array[3]=Vector3f(213, 548.8, 227);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	
	// ceiling
	array[0]=Vector3f(556, 548.8, 0);
	array[1]=Vector3f(556, 548.8, 559.2);
	array[2]=Vector3f(0, 548.8, 559.2);
	array[3]=Vector3f(0, 548.8, 0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	
	// back wall
	array[0]=Vector3f(549.6, 0, 559.2);
	array[1]=Vector3f(0, 0, 559.2);
	array[2]=Vector3f(0, 548.8, 559.2);
	array[3]=Vector3f(556, 548.8, 559.2);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	
	// right wall (green)
	array[0]=Vector3f(0, 0, 559.2);
	array[1]=Vector3f(0, 0, 0);
	array[2]=Vector3f(0, 548.8, 0);
	array[3]=Vector3f(0, 548.8, 559.2);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	
	// left wall (red)
	array[0]=Vector3f(552.8, 0, 0);
	array[1]=Vector3f(549.6, 0, 559.2);
	array[2]=Vector3f(556, 548.8, 559.2);
	array[3]=Vector3f(556, 548.8, 0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	
	// short block
	array[0]=Vector3f(130.0, 165.0,  65.0); 
	array[1]=Vector3f( 82.0, 165.0, 225.0);
	array[2]=Vector3f(240.0, 165.0, 272.0);
	array[3]=Vector3f(290.0, 165.0, 114.0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	array[0]=Vector3f(290.0,   0.0, 114.0);
	array[1]=Vector3f(290.0, 165.0, 114.0);
	array[2]=Vector3f(240.0, 165.0, 272.0);
	array[3]=Vector3f(240.0,   0.0, 272.0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	array[0]=Vector3f(130.0,   0.0,  65.0);
	array[1]=Vector3f(130.0, 165.0,  65.0);
	array[2]=Vector3f(290.0, 165.0, 114.0);
	array[3]=Vector3f(290.0,   0.0, 114.0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	array[0]=Vector3f( 82.0,   0.0, 225.0);
	array[1]=Vector3f( 82.0, 165.0, 225.0);
	array[2]=Vector3f(130.0, 165.0,  65.0);
	array[3]=Vector3f(130.0,   0.0,  65.0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	array[0]=Vector3f(240.0,   0.0, 272.0);
	array[1]=Vector3f(240.0, 165.0, 272.0);
	array[2]=Vector3f( 82.0, 165.0, 225.0);
	array[3]=Vector3f( 82.0,   0.0, 225.0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	
	// tall block
	array[0]=Vector3f(423.0, 330.0, 247.0);
	array[1]=Vector3f(265.0, 330.0, 296.0);
	array[2]=Vector3f(314.0, 330.0, 456.0);
	array[3]=Vector3f(472.0, 330.0, 406.0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	array[0]=Vector3f(423.0,   0.0, 247.0);
	array[1]=Vector3f(423.0, 330.0, 247.0);
	array[2]=Vector3f(472.0, 330.0, 406.0);
	array[3]=Vector3f(472.0,   0.0, 406.0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	array[0]=Vector3f(472.0,   0.0, 406.0);
	array[1]=Vector3f(472.0, 330.0, 406.0);
	array[2]=Vector3f(314.0, 330.0, 456.0);
	array[3]=Vector3f(314.0,   0.0, 456.0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	array[0]=Vector3f(314.0,   0.0, 456.0);
	array[1]=Vector3f(314.0, 330.0, 456.0);
	array[2]=Vector3f(265.0, 330.0, 296.0);
	array[3]=Vector3f(265.0,   0.0, 296.0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	array[0]=Vector3f(265.0,   0.0, 296.0);
	array[1]=Vector3f(265.0, 330.0, 296.0);
	array[2]=Vector3f(423.0, 330.0, 247.0);
	array[3]=Vector3f(423.0,   0.0, 247.0);
	patches.push_back(Patch(array, getVector(0.5, 0.5, 0.5), 0.5, 0));
	
	// subdivide the original patches
	subdivide();
	// subdivideTo16();
	
	/*
	cout << "Patches size is now " << patches.size() << endl;
	int i;
	for (i=0; i<patches.size(); i++) {
		cout << "Top left point for Patch " << i << " is " << patches[i].vertices[0] << endl;
		cout << "Top right point for Patch " << i << " is " << patches[i].vertices[1] << endl;
		cout << "Bottom right point for Patch " << i << " is " << patches[i].vertices[2] << endl;
		cout << "Bottom left point for Patch " << i << " is " << patches[i].vertices[3] << endl;
	}
	*/
	
}

void Scene::calcFormFactors() {
	int i, j;
	for (i=0; i<patches.size(); i++)
		for (j=0; j<patches.size(); j++)
			if (i != j) {
				// patches[i].viewFactors[j] = patches[i].formFactor(patches[j]);
				patches[i].viewFactors[j] = 0;
			}
}

void Scene::subdivideTo16() {
	subdivide(); // 2x2
	subdivide(); // 4x4
	subdivide(); // 8x8
	subdivide(); // 16x16
}

void Scene::subdivide() {
	vector<Patch> newPatches;
	int i;
	for (i=0; i<patches.size(); i++) {
		
		// Store the original patch properties.
		vector<float> origColor = patches[i].color;
		float origRefl = patches[i].reflectance;
		float origIrr = patches[i].irradiance;
		
		// Get the vertices of the current patch
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
