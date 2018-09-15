#ifndef LIGHT_H
#define LIGHT_H

#include "point.h"

class Light {
public:
	virtual Color getIntensity() =0;
	virtual Vector getDir(Point p) =0;
	virtual float getTmax(Point in) =0;
};

#endif

