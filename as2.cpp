#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>

#include "vect.h"
#include "point.h"
#include "ray.h"
#include "sphere.h"
#include "triangle.h"
#include "ellipsoid.h"

#include "light.h"
#include "dlight.h"
#include "plight.h"
#include "brdf.h"
#include "scene.h"
#include "color.h"
#include "primitive.h"
#include "readobj.h"
#include "tests.h"
#include "input-01.h"
#include "input-02.h"
#include "input-03.h"

using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: ./raytracer [scene#]\n");
		exit(0);
	}
	char* arg1 = argv[1];
	char scn = arg1[0];
	//printf("%s\n", sc);

	clock_t begin = clock();

	if (!strcmp(arg1, "01")) {
		input01();
	} else if (!strcmp(arg1, "02")) {
		input02();
	} else if (!strcmp(arg1, "03")) {
		input03();
	} else {
		printf("invalid scene number\n");
		exit(0);
	}

	/*
	if (scn == '1') {
		runtest1();
	} else if (scn == '3') {
		runtest3();
	} else if (scn == '5') {
		runtest5();
	} else if (scn == '6') {
		runtest6();
	} else if (scn == '7') {
		runtest7();
	} else if (scn == '8') {
		runtest8();
	} else if (scn == '9') {
		runtest9();
	} else {
		printf("invalid scene number\n");
		exit(0);
	}
	*/

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	printf("elapsed time: %f seconds\n", elapsed_secs);
}



