#ifndef VECT_H
#define VECT_H

#include <cmath>
#include <cstdio>

class Vector {
public:
	float x, y, z;
	Vector();
	Vector(float a, float b, float c);

	float dot(Vector a) const;
	Vector scale(float a) const;
	float length();
	Vector normalize();
	Vector sub(Vector a);
	Vector add(Vector a);
	Vector cross(Vector v);
	void print();
};

// not needed
class Normal: public Vector {
};

Vector::Vector() {
	x = y = z = 0;
}

Vector::Vector(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

float Vector::dot(Vector a) const {
	return a.x * x + a.y * y + a.z * z;
}

Vector Vector::scale(float a) const {
	return Vector(a*x, a*y, a*z);
}

float Vector::length() {
	return sqrt(x*x + y*y + z*z);
}

Vector Vector::normalize() {
	float len = length();
	return Vector(x/len, y/len, z/len);
}

Vector Vector::sub(Vector a) {
	return Vector(x-a.x, y-a.y, z-a.z);
}

Vector Vector::add(Vector a) {
	return Vector(x+a.x, y+a.y, z+a.z);
}

Vector Vector::cross(Vector v) {
	Vector ret;
	ret.x = y*v.z - z*v.y;
	ret.y = z*v.x - x*v.z;
	ret.z = x*v.y - y*v.x;
	return ret;
}

void Vector::print() {
	printf("Vector(%f %f %f)\n", x, y, z);
}

#endif

