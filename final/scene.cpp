#include "scene.h"

using namespace Eigen;

vector<float> getVector(float r, float g, float b) {
	float ar[] = {r, g, b};
	vector<float> v (&ar[0], &ar[3]);
	return v;
}

Scene::Scene() {
	vector<Vector3f> array(4);

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
}

