#include "vect.h"
#include "point.h"
#include "ray.h"
#include "primitive.h"
#include "brdf.h"
#include <cmath>

class Sphere : public Primitive {
public:
	float radius;
	Point center;
	BRDF brdf;
	int type;
	Sphere();
	Sphere(float r, Point c, BRDF b);

	int gettype();
	bool intersectP(const Ray& r);
	bool intersect(const Ray& r, Point* intersection, Vector* normal);
	BRDF getBRDF();
};

Sphere::Sphere() {
}

Sphere::Sphere(float r, Point c, BRDF b) {
	radius = r;
	center = c;
	brdf = b;
	type = 0;
}

int Sphere::gettype() {
	return type;
}

bool Sphere::intersectP(const Ray& r) {
	Point e = r.pos;
	Vector d = r.dir;
	Vector esubc = e.sub(center);

	// at^2 + bt + c = 0
	float a = d.dot(d);
	float b = d.scale(2).dot(esubc);
	float c = esubc.dot(esubc) - radius * radius;

	float discr = b*b - 4*a*c;
	if (discr < 0) {
		return false;
	}

	float sd = sqrt(discr);
	float t1 = (-b - sd) / (2*a);
	float t2 = (-b + sd) / (2*a);

	return r.inrange(t1) || r.inrange(t2);
}

bool Sphere::intersect(const Ray& r, Point* intersection, Vector* normal) {
	Point e = r.pos;
	Vector d = r.dir;
	Vector esubc = e.sub(center);

	// at^2 + bt + c = 0
	float a = d.dot(d);
	float b = d.scale(2).dot(esubc);
	float c = esubc.dot(esubc) - radius * radius;

	float discr = b*b - 4*a*c;
	if (discr < 0) {
		return false;
	}

	float sd = sqrt(discr);
	float t1 = (-b - sd) / (2*a);
	float t2 = (-b + sd) / (2*a);

	float realt;
	if (r.inrange(t1)) {
		if (r.inrange(t2)) {
			realt = fmin(t1, t2);
		} else {
			realt = t1;
		}
	} else {
		if (r.inrange(t2)) {
			realt = t2;
		} else {
			return false;
		}
	}

	*intersection = e.addvec(d.scale(realt));
	*normal = (*intersection).sub(center).normalize();

	return true;
}

BRDF Sphere::getBRDF() {
	return brdf;
}

