#include "patch.h"

using namespace Eigen;

Patch::Patch(vector<Vector3f> _points) {
	points = _points;
}

void Patch::print() {
	cout << "Patch" << endl;
	for (int a=0; a<4; a++) {
		for (int b=0; b<4; b++) {
			cout << "(";
			cout << points[a*4 + b](0, 0) << ", ";
			cout << points[a*4 + b](1, 0) << ", ";
			cout << points[a*4 + b](2, 0);
			cout << ") ";
		}
		cout << endl;
	}
	cout << endl;
}

vector<Vector3f> Patch::bezcurveinterp(vector<Vector3f> curve, float u) {
	//first, split each of the three segments
	// to form two new ones AB and BC
	vector<Vector3f> result;
	Vector3f A = curve[0] * (1.0 - u) + curve[1] * u;
	Vector3f B = curve[1] * (1.0 - u) + curve[2] * u;
	Vector3f C = curve[2] * (1.0 - u) + curve[3] * u;
	Vector3f D = A * (1.0 - u) + B * u;
	Vector3f E = B * (1.0 - u) + C * u;
	Vector3f p = D * (1.0 - u) + E * u;
	Vector3f dPdu = 3 * (E - D);
	result.push_back(p);
	result.push_back(dPdu);
	return result;		
}

vector<Vector3f> Patch::bezpatchinterp(float u, float v) {
	vector<vector<Vector3f> > points_v = controlForV();
	vector<vector<Vector3f> > points_u = controlForU();
	vector<Vector3f> vcurve;
	vector<Vector3f> ucurve;
	vector<Vector3f> surfaceDerivativeV;
	vector<Vector3f> surfaceDerivativeU;
	vector<Vector3f> result;
	vector<Vector3f> vcurve0 = bezcurveinterp(points_v[0], u);
	vector<Vector3f> vcurve1 = bezcurveinterp(points_v[1], u);
	vector<Vector3f> vcurve2 = bezcurveinterp(points_v[2], u);
	vector<Vector3f> vcurve3 = bezcurveinterp(points_v[3], u);
	vector<Vector3f> ucurve0 = bezcurveinterp(points_u[0], v);
	vector<Vector3f> ucurve1 = bezcurveinterp(points_u[1], v);
	vector<Vector3f> ucurve2 = bezcurveinterp(points_u[2], v);	
	vector<Vector3f> ucurve3 = bezcurveinterp(points_u[3], v);
		
	// build control points for a Bezier curve in v

	vcurve.push_back(vcurve0[0]);	
	vcurve.push_back(vcurve1[0]);
	vcurve.push_back(vcurve2[0]);	
	vcurve.push_back(vcurve3[0]);
	
	// build control points for a Bezier curve in u

	ucurve.push_back(ucurve0[0]);	
	ucurve.push_back(ucurve1[0]);
	ucurve.push_back(ucurve2[0]);	
	ucurve.push_back(ucurve3[0]);
	
	surfaceDerivativeV = bezcurveinterp(vcurve, v);
	surfaceDerivativeU = bezcurveinterp(ucurve, u);
	
	Vector3f dPdu = surfaceDerivativeU[1];
	Vector3f dPdv = surfaceDerivativeV[1];
	Vector3f n = dPdu.cross(dPdv);
	Vector3f norm = n / n.size();
	
	result.push_back(surfaceDerivativeU[0]);
	result.push_back(norm);
	return result;
}

void Patch::subdividepatch(float step) {
	// compute how many subdivisions there are
	// for this step size
	int numdiv = (1+0.001) / step;
	float u, v = 0;
	int size = numdiv * numdiv;
	int start = 0;
	int end = numdiv;
	
	// for each parametric value of u
	for (int iu=0; iu<numdiv; iu++) {
		u = iu * step;
		// for each parametric value of v
		for (int iv=0; iv<numdiv; iv++) {
			v = iv * step;
			// evaluate surface
			vector<Vector3f> pointAndNorm = bezpatchinterp(u,v);
			sdPoints.push_back(pointAndNorm[0]);
			sdNormals.push_back(pointAndNorm[1]);
		}
	}
	while (end+1 < size) {
		vector<Vector3f> quad;
		quad.push_back(sdPoints[start]);
		quad.push_back(sdPoints[start+1]);
		quad.push_back(sdPoints[end]);
		quad.push_back(sdPoints[end+1]);
		quad.push_back(sdNormals[start]);
		quad.push_back(sdNormals[start+1]);
		quad.push_back(sdNormals[end]);
		quad.push_back(sdNormals[end+1]);
		quads.push_back(quad);
		start += 2;
		end = start + numdiv;
	}
	
}

vector<vector<Vector3f> > Patch::controlForV() {
	vector<vector<Vector3f> > results;
	vector<Vector3f> row1;
	row1.push_back(points[0]);
	row1.push_back(points[1]);
	row1.push_back(points[2]);
	row1.push_back(points[3]);
	vector<Vector3f> row2;
	row2.push_back(points[4]);
	row2.push_back(points[5]);
	row2.push_back(points[6]);
	row2.push_back(points[7]);
	vector<Vector3f> row3;
	row3.push_back(points[8]);
	row3.push_back(points[9]);
	row3.push_back(points[10]);
	row3.push_back(points[11]);
	vector<Vector3f> row4;
	row4.push_back(points[12]);
	row4.push_back(points[13]);
	row4.push_back(points[14]);
	row4.push_back(points[15]);
	results.push_back(row1);
	results.push_back(row2);
	results.push_back(row3);
	results.push_back(row4);
	return results;
}

vector<vector<Vector3f> > Patch::controlForU() {
	vector<vector<Vector3f> > results;
	vector<Vector3f> row1;
	row1.push_back(points[0]);
	row1.push_back(points[4]);
	row1.push_back(points[8]);
	row1.push_back(points[12]);
	vector<Vector3f> row2;
	row2.push_back(points[1]);
	row2.push_back(points[5]);
	row2.push_back(points[8]);
	row2.push_back(points[13]);
	vector<Vector3f> row3;
	row3.push_back(points[2]);
	row3.push_back(points[6]);
	row3.push_back(points[10]);
	row3.push_back(points[14]);
	vector<Vector3f> row4;
	row4.push_back(points[3]);
	row4.push_back(points[7]);
	row4.push_back(points[11]);
	row4.push_back(points[15]);
	results.push_back(row1);
	results.push_back(row2);
	results.push_back(row3);
	results.push_back(row4);
	return results;
}

