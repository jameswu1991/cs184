#include "sphere.h"

Sphere::Sphere() {
}

Sphere::Sphere (Vertex c, float rad) {
	center = c;
	radius = rad;
}

void Sphere::scale(float f) {
	radius = radius*f;
}

Vertex Sphere::normal(Vertex v) {
	return v.normalize();
}

vector<float> Sphere::intersect(Ray ray) {
	Vertex ve = ray.getOrigin();
	Vertex vd = ray.getDirection();
	vector<float> allT;
	float t1 = 0;
	float t2 = 0;
	float discriminant = pow(vd.dot(ve.sub(center)), 2) - (vd.dot(vd))*((ve.sub(center)).dot(ve.sub(center)) - pow(radius, 2));
	if (discriminant < 0)
	{
		return allT;
	}
	else if (discriminant == 0) 
	{
		t1 = (vd.dot(ve.sub(center)))/(vd.dot(vd)) * -1;
		allT.push_back(t1);
		return allT;		
	}
	else 
	{
		t1 = ((vd.dot(ve.sub(center))) + sqrt(discriminant))/(vd.dot(vd)) * -1;
		t2 = ((vd.dot(ve.sub(center))) - sqrt(discriminant))/(vd.dot(vd)) * -1;
		allT.push_back(t1);
		allT.push_back(t2);
		//printf("Pushing %f %f\n", t1, t2);
		//printf("Size of allT is %d\n", allT.size());
		return allT;
	}
	return allT;
}

