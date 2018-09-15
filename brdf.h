#ifndef BRDF_H
#define BRDF_H

#include "color.h"

class BRDF {
public:
	Color kd, ks, ka, kr;
	BRDF();
	BRDF(Color _kd, Color _ks, Color _ka, Color _kr);
};

BRDF::BRDF() {
	//printf("*** bad constructor\n");
};

BRDF::BRDF(Color _kd, Color _ks, Color _ka, Color _kr) {
	kd = _kd;
	ks = _ks;
	ka = _ka;
	kr = _kr;
}

#endif

