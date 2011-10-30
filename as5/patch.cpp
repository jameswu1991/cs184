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
	n = n / n.size();
	
	result.push_back(surfaceDerivativeU[0]);
	result.push_back(n);
	return result;
}

Vector2f midpoint (Vector2f p1, Vector2f p2) {
	return (p1+p2)/2;
}

Triangle::Triangle (Vector2f _p1, Vector2f _p2, Vector2f _p3) {
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
}

MatrixXf Triangle::getMatrix() {
	MatrixXf m (3, 6);
	m << p1(0), p1(1), 0,
		p2(0), p2(1), 0,
		p3(0), p3(1), 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0;
	return m.transpose();
}

vector<Triangle> Triangle::divide(bool side1, bool side2, bool side3, bool center) {
	vector<Triangle> subtriangles;
	if (side1 && side2 && side3) {
		subtriangles.push_back(Triangle(p1, midpoint(p1, p2), midpoint(p1, p3)));
		subtriangles.push_back(Triangle(midpoint(p1, p2), p2, midpoint(p2, p3)));
		subtriangles.push_back(Triangle(midpoint(p1, p3), midpoint(p2, p3), p3));
		subtriangles.push_back(Triangle(midpoint(p1, p2), midpoint(p2, p3), midpoint(p3, p1)));
	}
	if (side1 && side2 && !side3) {
		subtriangles.push_back(Triangle(p1, midpoint(p1, p2), midpoint(p1, p3)));
		subtriangles.push_back(Triangle(midpoint(p1, p2), p2, midpoint(p1, p3)));
		subtriangles.push_back(Triangle(midpoint(p1, p3), p2, p3));
	}
	if (side1 && !side2 && side3) {
		subtriangles.push_back(Triangle(p1, midpoint(p1, p2), p3));
		subtriangles.push_back(Triangle(midpoint(p1, p2), p2, midpoint(p2, p3)));
		subtriangles.push_back(Triangle(midpoint(p1, p2), midpoint(p2, p3), p3));
	}
	if (!side1 && side2 && side3) {
		subtriangles.push_back(Triangle(p1, p2, midpoint(p2, p3)));
		subtriangles.push_back(Triangle(p1, midpoint(p2, p3), midpoint(p1, p3)));
		subtriangles.push_back(Triangle(midpoint(p1, p3), midpoint(p2, p3), p3));
	}
	if (side1 && !side2 && !side3) {
		subtriangles.push_back(Triangle(p1, midpoint(p1, p2), p3));
		subtriangles.push_back(Triangle(midpoint(p1, p2), p2, p3));
	}
	if (!side1 && side2 && !side3) {
		subtriangles.push_back(Triangle(p1, p2, midpoint(p1, p3)));
		subtriangles.push_back(Triangle(midpoint(p2, p3), p2, p3));
	}
	if (!side1 && !side2 && side3) {
		subtriangles.push_back(Triangle(p1, p2, midpoint(p2, p3)));
		subtriangles.push_back(Triangle(p1, midpoint(p2, p3), p3));
	}
	if (!side1 && !side2 && !side3) {
		subtriangles.push_back(Triangle(p1, p2, p3));
	}
	return subtriangles;
}

void Patch::tessellate(float error) {
	// bezpatchinterp(u, v);
}

void Patch::subdividepatch(float step) {
	// compute how many subdivisions there are
	// for this step size
	step = 0.1;
	int numdiv = ((1 + 0.001) / step) + 1;
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
			if (pointAndNorm[1].norm() == 0) {
				vector<Vector3f> next = bezpatchinterp((iu+1)*step, (iv+1)*step);
				pointAndNorm[1] = next[1];
			}

			sdPoints.push_back(pointAndNorm[0]);
			sdNormals.push_back(pointAndNorm[1]);
		}
	}

	while ((end+1) < size) {
		MatrixXf quad (3,8);
		// add point vectors
		quad(0,0) = sdPoints[start](0,0);
		quad(1,0) = sdPoints[start](1,0);
		quad(2,0) = sdPoints[start](2,0);
		quad(0,1) = sdPoints[end](0,0);
		quad(1,1) = sdPoints[end](1,0);
		quad(2,1) = sdPoints[end](2,0);
		quad(0,2) = sdPoints[end+1](0,0);
		quad(1,2) = sdPoints[end+1](1,0);
		quad(2,2) = sdPoints[end+1](2,0);
		quad(0,3) = sdPoints[start+1](0,0);
		quad(1,3) = sdPoints[start+1](1,0);
		quad(2,3) = sdPoints[start+1](2,0);

		// add normal vectors
		quad(0,4) = sdNormals[start](0,0);
		quad(1,4) = sdNormals[start](1,0);
		quad(2,4) = sdNormals[start](2,0);
		quad(0,5) = sdNormals[end](0,0);
		quad(1,5) = sdNormals[end](1,0);
		quad(2,5) = sdNormals[end](2,0);
		quad(0,6) = sdNormals[end+1](0,0);
		quad(1,6) = sdNormals[end+1](1,0);
		quad(2,6) = sdNormals[end+1](2,0);
		quad(0,7) = sdNormals[start+1](0,0);
		quad(1,7) = sdNormals[start+1](1,0);
		quad(2,7) = sdNormals[start+1](2,0);
		quads.push_back(quad);
		start += 1;
		if ((start % numdiv) == (numdiv-1)) {
			start += 1;
		}
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
	row2.push_back(points[9]);
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

