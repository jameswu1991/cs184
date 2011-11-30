#include "patch.h"

using namespace std;
using namespace Eigen;

/*
public:
vector<Vector3f> vertices;
vector<float> color;
float reflectance;
float irradiance;
map<Patch, float> viewFactors;
*/

Patch::Patch(vector<Vector3f> _vertices, vector<float> _color, float _reflectance, float _irradiance){
	vertices = _vertices;
	color = _color;
	reflectance = _reflectance;
	irradiance = _irradiance;
}
