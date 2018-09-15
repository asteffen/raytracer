#ifndef PLIGHT_H
#define PLIGHT_H

#include "light.h"

class PLight : public Light {
public:
	Color intensity;
	Point pos;
	PLight(Color i, Point p);

	Color getIntensity();
	Vector getDir(Point p);
	float getTmax(Point in);
};

PLight::PLight(Color i, Point p) {
	intensity = i;
	pos = p;
}

Color PLight::getIntensity() {
	return intensity;
}

Vector PLight::getDir(Point p) {
	return p.sub(pos).normalize();
}

float PLight::getTmax(Point in) {
	return in.sub(pos).length();
}

#endif

