#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "brdf.h"

class Primitive {
public:
	//BRDF* brdf; // member of abstract class causes weird errors
	virtual BRDF getBRDF() =0;
	virtual int gettype() =0;
	virtual bool intersectP(const Ray& r) =0;
	virtual bool intersect(const Ray& r, Point* intersection, Vector* normal) =0;
};

#endif

