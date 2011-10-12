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

Ray Sphere::intersect(Ray ray) {
	Ray intersection (Vertex(0,0,0), Vertex(0,0,0));
	Vertex ve = ray.getOrigin();
	Vertex vd = ray.getDirection();
	float t1 = 0;
	float t2 = 0;
	float discriminant = pow(vd.dot(ve.sub(center)), 2) - (vd.dot(vd))*((ve.sub(center)).dot(ve.sub(center)) - pow(radius, 2));
	if (discriminant < 0)
	{
		return intersection;
	}
	else if (discriminant == 0) 
	{
		t1 = ((vd.dot(ve.sub(center))) *-1)/(vd.dot(vd));
		if (t1 > 0) {
			Vertex intersect = ray.getOrigin().add(ray.getDirection().scale(t1 - 0.0001));
			Vertex norm = center.sub(intersect).normalize();
			if (norm.get(2)>0)
				norm = norm.scale(-1);
			intersection.setOrigin(intersect);
			intersection.setDirection(norm);
		}
		return intersection;	
	}
	else 
	{
		t1 = (((vd.dot(ve.sub(center))) * -1) + sqrt(discriminant))/(vd.dot(vd));
		t2 = (((vd.dot(ve.sub(center))) * -1) - sqrt(discriminant))/(vd.dot(vd));
		if ((t1 < 0) && (t2 < 0)) {
			return intersection;
		}
		else if ((t1 < 0) && (t2 > 0)) {
			Vertex intersect = ray.getOrigin().add(ray.getDirection().scale(t2 - 0.0001));
			Vertex norm = center.sub(intersect).normalize();
			if (norm.get(2)>0)
				norm = norm.scale(-1);
			intersection.setOrigin(intersect);
			intersection.setDirection(norm);
		}
		else if ((t2 < 0) && (t1 > 0)) {
			Vertex intersect = ray.getOrigin().add(ray.getDirection().scale(t1 - 0.0001));
			Vertex norm = center.sub(intersect).normalize();
			if (norm.get(2)>0)
				norm = norm.scale(-1);
			intersection.setOrigin(intersect);
			intersection.setDirection(norm);
		}
		else if (t1 < t2) {
			Vertex intersect = ray.getOrigin().add(ray.getDirection().scale(t1 - 0.0001));
			Vertex norm = center.sub(intersect).normalize();
			if (norm.get(2)>0)
				norm = norm.scale(-1);
			intersection.setOrigin(intersect);
			intersection.setDirection(norm);
		}
		else if (t2 < t1) {
			Vertex intersect = ray.getOrigin().add(ray.getDirection().scale(t2 - 0.0001));
			Vertex norm = center.sub(intersect).normalize();
			if (norm.get(2)>0)
				norm = norm.scale(-1);
			intersection.setOrigin(intersect);
			intersection.setDirection(norm);
		}
		else {
			return intersection;
		}
		return intersection;
	}
	return intersection;
}

bool Sphere::intersect_b(Ray ray) {
	Vertex ve = ray.getOrigin();
	Vertex vd = ray.getDirection();
	float t1 = 0;
	float t2 = 0;
	float discriminant = pow(vd.dot(ve.sub(center)), 2) - (vd.dot(vd))*((ve.sub(center)).dot(ve.sub(center)) - pow(radius, 2));
	//cout << discriminant << endl;
	if (discriminant < 0)
	{
		return false;
	}
	else if (discriminant == 0) 
	{
		t1 = ((vd.dot(ve.sub(center))) *-1)/(vd.dot(vd));
		if (t1 > 0) {
		return true;
		}
	}
	else {
		t1 = (((vd.dot(ve.sub(center))) * -1) + sqrt(discriminant))/(vd.dot(vd));
		t2 = (((vd.dot(ve.sub(center))) * -1) - sqrt(discriminant))/(vd.dot(vd));
		if ((t1 > 0) || (t2 > 0)) {
			return true;
		}
	}
	return false;
}

bool Sphere::unitIntersect_b(Ray ray) {
	Vertex ve = ray.getOrigin();
	Vertex vd = ray.getDirection();
	float t1 = 0;
	float t2 = 0;
	Vertex cent = Vertex(0,0,0);
	float rad = 1;
	float discriminant = pow(vd.dot(ve.sub(cent)), 2) - (vd.dot(vd))*((ve.sub(cent)).dot(ve.sub(cent)) - pow(rad, 2));
	//cout << discriminant << endl;
	if (discriminant < 0)
	{
		return false;
	}
	else if (discriminant == 0) 
	{
		t1 = ((vd.dot(ve.sub(cent))) *-1)/(vd.dot(vd));
		if (t1 > 0) {
		return true;
		}
	}
	else {
		t1 = (((vd.dot(ve.sub(cent))) * -1) + sqrt(discriminant))/(vd.dot(vd));
		t2 = (((vd.dot(ve.sub(cent))) * -1) - sqrt(discriminant))/(vd.dot(vd));
		if ((t1 > 0) || (t2 > 0)) {
			return true;
		}
	}
	return false;
}


