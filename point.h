#ifndef POINT_H
#define POINT_H

#include <cstdio>
#include "vect.h"

class Point {
public:
	float x, y, z;
	Point();
	Point(float a, float b, float c);

	Point addvec(Vector a) const;
	Point subvec(Vector a);
	Vector sub(Point p);
	Point scale(float a);
	Point add(Point p);
	void print();
};

Point::Point() {
	x = y = z = 0;
}

Point::Point(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

Point Point::addvec(Vector a) const {
	return Point(x + a.x, y + a.y, z + a.z);
}

Point Point::subvec(Vector a) {
	return Point(x - a.x, y - a.y, z - a.z);
}

Vector Point::sub(Point p) {
	return Vector(x - p.x, y - p.y, z - p.z);
}

Point Point::scale(float a) {
	return Point(a*x, a*y, a*z);
}

Point Point::add(Point p) {
	return Point(x+p.x, y+p.y, z+p.z);
}

void Point::print() {
	printf("Point(%f %f %f)\n", x, y, z);
}

#endif

