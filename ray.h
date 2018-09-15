#ifndef RAY_H
#define RAY_H

#include <cstdio>
#include "vect.h"
#include "point.h"

class Ray {
public:
	Point pos;
	Vector dir;
	float tmin, tmax;
	Ray(const Point& p, const Vector& v, float _tmin, float _tmax);

	bool inrange(float t) const;
	void print();
};

Ray::Ray(const Point& p, const Vector& v, float _tmin, float _tmax) {
	pos = p;
	dir = v;
	tmin = _tmin;
	tmax = _tmax;
}

bool Ray::inrange(float t) const {
	return (tmin <= t) && (t <= tmax);
}

void Ray::print() {
	printf("Ray pos=(%f %f %f), dir=(%f %f %f)\n",
		pos.x, pos.y, pos.z, dir.x, dir.y, dir.z);
}

#endif

