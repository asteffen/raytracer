#ifndef DLIGHT_H
#define DLIGHT_H

#include <cfloat>
#include "light.h"

class DLight : public Light {
public:
	Color intensity;
	Vector dir;
	DLight(Color i, Vector d);

	Color getIntensity();
	Vector getDir(Point p);
	float getTmax(Point in);
};

DLight::DLight(Color i, Vector d) {
	intensity = i;
	dir = d.normalize();
}

Color DLight::getIntensity() {
	return intensity;
}

Vector DLight::getDir(Point p) {
	return dir;
}

float DLight::getTmax(Point in) {
	return FLT_MAX;
}

#endif

