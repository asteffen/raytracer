#include "point.h"
#include "scene.h"


void runtest1() {
	Point eye = Point(0, 0, 0);
	Point ul = Point(-1, 1, -3);
	Point ur = Point(1, 1, -3);
	Point lr = Point(1, -1, -3);
	Point ll = Point(-1, -1, -3);
	int w = 500;
	int h = 500;

	float t = 0.57735027;

	Color intensity1 = Color(1, 1, 1);
	Vector dir1 = Vector(t, -t, -t);
	//dir1 = dir1.scale(-1);
	DLight dlight1 = DLight(intensity1, dir1);

	Color intensity2 = Color(0, 0, 1);
	Vector dir2 = Vector (t, t, -t);
	DLight dlight2 = DLight(intensity2, dir2);

	std::vector<Light*> lights;
	lights.push_back(&dlight1);
	lights.push_back(&dlight2);

	float radius1 = 3.0;
	Point center1 = Point(0, 0, -20);
	Color ka1 = Color(0.1, 0.1, 0.1);
	//Color ka1 = Color(0, 1, 0);
	Color kd1 = Color(1, 0, 1);
	Color ks1 = Color(1, 1, 1);
	Color kr1 = Color(0, 0, 0);

	BRDF brdf1 = BRDF(kd1, ks1, ka1, kr1);

	Sphere s1 = Sphere(radius1, center1, brdf1);

	float radius2 = 1.0;
	Point center2 = Point(-2, 2, -15);
	Color ka2 = Color(0.1, 0.1, 0.1);
	Color kd2 = Color(1, 1, 0);
	Color ks2 = ks1;
	Color kr2 = kr1;

	BRDF brdf2 = BRDF(kd2, ks2, ka2, kr2);
	Sphere s2 = Sphere(radius2, center2, brdf2);

	float radius3 = 1.0;
	Point center3 = Point(-2, -2, -15);
	Color kd3 = Color(0, 1, 1);
	BRDF brdf3 = BRDF(kd3, ks2, ka2, kr2);
	Sphere s3 = Sphere(radius3, center3, brdf3);

	Point v1 = Point(5, 5, -17);
	Point v2 = Point(1, 4, -20);
	Point v3 = Point(6, -1, -20);
	Color ka4 = Color(0.1, 0.1, 0.1);
	//Color ka4 = Color(1, 1, 1);
	Color kd4 = ka1;
	Color ks4 = Color(1, 1, 1);
	Color kr4 = Color(1, 1, 1);
	BRDF brdf4 = BRDF(kd4, ks4, ka4, kr4);
	Triangle t4 = Triangle(v1, v2, v3, brdf4);

	// test spheres
	Sphere s5 = Sphere(0.3, v1, brdf1);
	Sphere s6 = Sphere(0.3, v2, brdf1);
	Sphere s7 = Sphere(0.3, v3, brdf1);

	std::vector<Primitive*> prims;
	prims.push_back(&s1);
	prims.push_back(&s2);
	prims.push_back(&s3);
	prims.push_back(&t4);
	prims.push_back(&s5);
	prims.push_back(&s6);
	prims.push_back(&s7);

	Scene test1 = Scene(eye, ul, ur, lr, ll, w, h,
		prims, lights);

	test1.render();
}

/*
// reflective spheres
void runtest2() {
	Point eye = Point(0, 0, 0);
	Point ul = Point(-1, 1, -3);
	Point ur = Point(1, 1, -3);
	Point lr = Point(1, -1, -3);
	Point ll = Point(-1, -1, -3);
	int w = 1000;
	int h = 1000;

	float t = 0.57735027;
	Color intensity1 = Color(1, 1, 1);
	Vector dir1 = Vector(t, -t, -t);
	Vector dir2 = Vector(-t, t, t);
	DLight dlight1 = DLight(intensity1, dir1);
	DLight dlight2 = DLight(intensity1, dir2);

	Light* lights[2];
	lights[0] = &dlight1;
	lights[1] = &dlight2;

	Color kau = Color(0.1, 0.1, 0.1);
	Color ksu = Color(1, 1, 1);
	Color kru = Color(0.9, 0.9, 0.9);

	Color kd1 = Color(1, 0, 0);
	Color kd2 = Color(0, 1, 0);
	Color kd3 = Color(0, 0, 1);
	Color kd4 = Color(1, 1, 0);
	Color kd5 = Color(0, 1, 1);
	BRDF brdf1 = BRDF(kd1, ksu, kau, kru);
	BRDF brdf2 = BRDF(kd2, ksu, kau, kru);
	BRDF brdf3 = BRDF(kd3, ksu, kau, kru);
	BRDF brdf4 = BRDF(kd4, ksu, kau, kru);
	BRDF brdf5 = BRDF(kd5, ksu, kau, kru);

	Point center1 = Point(0, 0, -17);
	Point center2 = Point(0, 4, -17);
	Point center3 = Point(0, -4, -17);
	Point center4 = Point(4, 0, -17);
	Point center5 = Point(-4, 0, -17);

	Sphere s1 = Sphere(2, center1, brdf1);
	Sphere s2 = Sphere(1.5, center2, brdf2);
	Sphere s3 = Sphere(1.5, center3, brdf3);
	Sphere s4 = Sphere(1.5, center4, brdf4);
	Sphere s5 = Sphere(1.5, center5, brdf5);

	Primitive* prims[5] = {&s1, &s2, &s3, &s4, &s5};

	Scene test2 = Scene(eye, ul, ur, lr, ll, w, h,
		prims, 5, lights, 2);

	test2.render();
}
*/

// ellipsoids. refl
void runtest3() {
	Point eye = Point(0, 0, 0);
	Point ul = Point(-1, 1, -3);
	Point ur = Point(1, 1, -3);
	Point lr = Point(1, -1, -3);
	Point ll = Point(-1, -1, -3);
	int w = 1000;
	int h = 1000;

	float t = 0.57735027;
	Color intensity1 = Color(1, 1, 1);
	Vector dir1 = Vector(t, -t, -t);
	Vector dir2 = Vector(-t, t, t);
	DLight dlight1 = DLight(intensity1, dir1);
	DLight dlight2 = DLight(intensity1, dir2);

	std::vector<Light*> lights;
	lights.push_back(&dlight1);
	lights.push_back(&dlight2);

	Color kau = Color(0.1, 0.1, 0.1);
	Color ksu = Color(1, 1, 1);
	Color kru = Color(0.9, 0.9, 0.9);

	Color kd1 = Color(1, 0, 0); // changed
	Color kd2 = Color(0, 1, 0);
	Color kd3 = Color(0, 0, 1);
	Color kd4 = Color(1, 1, 0);
	Color kd5 = Color(0, 1, 1);
	BRDF brdf1 = BRDF(kd1, ksu, kau, kru);
	BRDF brdf2 = BRDF(kd2, ksu, kau, kru);
	BRDF brdf3 = BRDF(kd3, ksu, kau, kru);
	BRDF brdf4 = BRDF(kd4, ksu, kau, kru);
	BRDF brdf5 = BRDF(kd5, ksu, kau, kru);

	Point center1 = Point(0, 0, -17);
	Vector scale1 = Vector(4, 2, 2);
	Vector rot1 = Vector(0, 0, 0);
	Ellipsoid e1 = Ellipsoid(center1, scale1, rot1, brdf1);

	Point center2 = Point(-2, 4, -17);
	Vector scale2 = Vector(0.5, 1.5, 1);
	Vector rot2 = Vector(0, -45, -45);
	Ellipsoid e2 = Ellipsoid(center2, scale2, rot2, brdf2);

	Point center3 = Point(-2, -4, -17);
	Vector scale3 = Vector(0.5, 1.5, 1);
	Vector rot3 = Vector(0, -45, 45);
	Ellipsoid e3 = Ellipsoid(center3, scale3, rot3, brdf3);

	Point center4 = Point(2, 4, -17);
	Vector scale4 = Vector(0.5, 1.5, 1);
	Vector rot4 = Vector(0, 45, -135);
	Ellipsoid e4 = Ellipsoid(center4, scale4, rot4, brdf4);

	Point center5 = Point(2, -4, -17);
	Vector scale5 = Vector(0.5, 1.5, 1);
	Vector rot5 = Vector(0, 45, 135);
	Ellipsoid e5 = Ellipsoid(center5, scale5, rot5, brdf5);

	//Primitive* prims[5] = {&e1, &e2, &e3, &e4, &e5};
	std::vector<Primitive*> prims;
	prims.push_back(&e1);
	prims.push_back(&e2);
	prims.push_back(&e3);
	prims.push_back(&e4);
	prims.push_back(&e5);

	Scene test3 = Scene(eye, ul, ur, lr, ll, w, h,
		prims, lights);

	test3.render();
}

// obj humanoid
void runtest4() {
	std::vector<Primitive*> prims;

	Color kau = Color(0.1, 0.1, 0.1);
	//Color ksu = Color(1, 1, 1);
	Color ksu = Color(0, 0, 0);
	//Color kru = Color(0.9, 0.9, 0.9);
	Color kru = Color(0, 0, 0);
	//Color kd1 = Color(1, 0, 0);
	Color kd1 = Color(1, 0, 0);
	BRDF brdf11 = BRDF(kd1, ksu, kau, kru);
	char* file = (char*) "obj/humanoid_quad.obj.txt";
	readobj(file, &prims, brdf11);

	/////

	float t = 0.57735027;
	Color intensity1 = Color(0.4,0.4,0.4);
	Vector dir1 = Vector(t, -t, -t);
	Vector dir2 = Vector(-t, t, -t);
	//Vector dir2 = dir1.scale(-1);
	//Vector dir2 = Vector(-0.850651,  0,  0.525731); // pt[5]
	DLight dlight1 = DLight(intensity1, dir1);
	DLight dlight2 = DLight(intensity1, dir2);

	std::vector<Light*> lights;
	lights.push_back(&dlight1);
	lights.push_back(&dlight2);

	Point eye = Point(-25, 0, 10);
	Vector dir = Vector(1, 0, 0);
	Vector up = Vector(0, 0, 1);
	Point ul, ur, lr, ll;
	setview(eye, dir, up, 3, &ul, &ur, &lr, &ll);

	int w = 300;
	int h = 300;

	Scene test3 = Scene(eye, ul, ur, lr, ll, w, h,
		prims, lights);

	test3.render();
}

// shuttle
void runtest5() {
	std::vector<Primitive*> prims;

	Color kau = Color(0,0,0);
	//Color ksu = Color(1, 1, 1);
	Color ksu = Color(1,1,1);
	//Color kru = Color(0.9, 0.9, 0.9);
	Color kru = Color(0, 0, 0);
	//Color kd1 = Color(1, 0, 0);
	Color kd1 = Color(1, 0, 0);
	BRDF brdf11 = BRDF(kd1, ksu, kau, kru);
	char* file = (char*) "obj/shuttle.obj.txt";
	readobj(file, &prims, brdf11);

	/////

	float t = 0.57735027;
	Color intensity1 = Color(1,1,1).scale(0.6);
	Vector dir1 = Vector(t, -t, -t);
	Vector dir2 = Vector(-t, t, -t);
	//Vector dir2 = dir1.scale(-1);
	//Vector dir2 = Vector(-0.850651,  0,  0.525731); // pt[5]
	DLight dlight1 = DLight(intensity1, dir1);
	DLight dlight2 = DLight(intensity1, dir2);

	std::vector<Light*> lights;
	lights.push_back(&dlight1);
	lights.push_back(&dlight2);

	Point eye = Point(20, -40, 20).scale(0.6);
	Vector dir = Vector(-1, 2, -1);
	//Vector up = Vector(0, -1.0/2, 1);
	Vector up = proj_perp(Vector(0, 0, 1), dir);
	Point ul, ur, lr, ll;
	setview(eye, dir, up, 3, &ul, &ur, &lr, &ll);

	Color ka2 = Color(0,0,0);
	Color ks2 = Color(0,0,0);
	//Color kr2 = Color(0, 0, 0);
	Color kr2 = Color(1,1,1);
	Color kd2 = Color(1, 1,1);
	BRDF brdf2 = BRDF(kd2, ks2, ka2, kr2);
	Point center2 = Point(-10,20,-10);
	Sphere s2 = Sphere(16, center2, brdf2);

	prims.push_back(&s2);

	int ww = 640;
	int w = ww;
	int h = ww;

	Scene test3 = Scene(eye, ul, ur, lr, ll, w, h,
		prims, lights);

	test3.render();
}

// weird ellipsoid with reflections
void runtest6() {
	std::vector<Primitive*> prims;

	Color kau = Color(0.1, 0.1, 0.1);
	Color ksu = Color(1, 1, 1);
	Color kru = Color(0.9, 0.9, 0.9);

	Color kd1 = Color(1, 0, 0); // changed
	Color kd2 = Color(0, 1, 0);
	Color kd3 = Color(0, 0, 1);
	Color kd4 = Color(1, 1, 0);
	Color kd5 = Color(0, 1, 1);
	BRDF brdf1 = BRDF(kd1, ksu, kau, kru);
	BRDF brdf2 = BRDF(kd2, ksu, kau, kru);
	BRDF brdf3 = BRDF(kd3, ksu, kau, kru);
	BRDF brdf4 = BRDF(kd4, ksu, kau, kru);
	BRDF brdf5 = BRDF(kd5, ksu, kau, kru);

	/////

	float t = 0.57735027;
	Color intensity1 = Color(1,1,1).scale(0.6);
	Vector dir1 = Vector(t, -t, -t);
	Vector dir2 = Vector(-t, t, -t);
	//Vector dir2 = dir1.scale(-1);
	//Vector dir2 = Vector(-0.850651,  0,  0.525731); // pt[5]
	DLight dlight1 = DLight(intensity1, dir1);
	DLight dlight2 = DLight(intensity1, dir2);

	std::vector<Light*> lights;
	lights.push_back(&dlight1);
	lights.push_back(&dlight2);

	Point eye = Point(20, -40, 20).scale(0.6);
	Vector dir = Vector(-1, 2, -1);
	//Vector up = Vector(0, -1.0/2, 1);
	Vector up = proj_perp(Vector(0, 0, 1), dir);
	Point ul, ur, lr, ll;
	setview(eye, dir, up, 3, &ul, &ur, &lr, &ll);

	Point center1 = Point(0, -6, 0);
	Vector scale1 = Vector(4, 2, 2).scale(1.1);
	Vector rot1 = Vector(-45, 0, 0);
	Ellipsoid e1 = Ellipsoid(center1, scale1, rot1, brdf1);

	Point center2 = Point(0, 6, 0);
	Vector scale2 = Vector(4, 2, 2).scale(1.5);
	Vector rot2 = Vector(0, 0, 0);
	Ellipsoid e2 = Ellipsoid(center2, scale2, rot2, brdf2);

	float z = -12;
	Point p1 = Point(-10000,10000,z);
	Point p2 = Point(10000,10000,z);
	Point p3 = Point(0,-10000,z);
	Triangle t3 = Triangle(p1, p2, p3, brdf3);

	prims.push_back(&e1);
	prims.push_back(&e2);
	prims.push_back(&t3);

	int w = 300;
	int h = 300;

	Scene test3 = Scene(eye, ul, ur, lr, ll, w, h,
		prims, lights);

	test3.render();
}

// ellipsoids. plight
void runtest7() {
	Point eye = Point(0, 0, 0);
	Point ul = Point(-1, 1, -3);
	Point ur = Point(1, 1, -3);
	Point lr = Point(1, -1, -3);
	Point ll = Point(-1, -1, -3);
	int w = 1000;
	int h = 1000;

	float t = 1;
	Color intensity1 = Color(1, 1, 1).scale(0.6);
	Vector dir1 = Vector(t, -t, -t);
	Point pt1 = Point(0,0,0).addvec(dir1.scale(20));
	Point pt2 = Point(0,0,0).addvec(dir1.scale(-20));
	PLight plight1 = PLight(intensity1, pt1);
	PLight plight2 = PLight(intensity1, pt2);

	std::vector<Light*> lights;
	lights.push_back(&plight1);
	lights.push_back(&plight2);

	Color kau = Color(0.1, 0.1, 0.1);
	Color ksu = Color(1, 1, 1);
	Color kru = Color(0.9, 0.9, 0.9);

	Color kd1 = Color(1, 0, 0); // changed
	Color kd2 = Color(0, 1, 0);
	Color kd3 = Color(0, 0, 1);
	Color kd4 = Color(1, 1, 0);
	Color kd5 = Color(0, 1, 1);
	BRDF brdf1 = BRDF(kd1, ksu, kau, kru);
	BRDF brdf2 = BRDF(kd2, ksu, kau, kru);
	BRDF brdf3 = BRDF(kd3, ksu, kau, kru);
	BRDF brdf4 = BRDF(kd4, ksu, kau, kru);
	BRDF brdf5 = BRDF(kd5, ksu, kau, kru);

	Point center1 = Point(0, 0, -17);
	Vector scale1 = Vector(4, 2, 2);
	Vector rot1 = Vector(0, 0, 0);
	Ellipsoid e1 = Ellipsoid(center1, scale1, rot1, brdf1);

	Point center2 = Point(-2, 4, -17);
	Vector scale2 = Vector(0.5, 1.5, 1);
	Vector rot2 = Vector(0, -45, -45);
	Ellipsoid e2 = Ellipsoid(center2, scale2, rot2, brdf2);

	Point center3 = Point(-2, -4, -17);
	Vector scale3 = Vector(0.5, 1.5, 1);
	Vector rot3 = Vector(0, -45, 45);
	Ellipsoid e3 = Ellipsoid(center3, scale3, rot3, brdf3);

	Point center4 = Point(2, 4, -17);
	Vector scale4 = Vector(0.5, 1.5, 1);
	Vector rot4 = Vector(0, 45, -135);
	Ellipsoid e4 = Ellipsoid(center4, scale4, rot4, brdf4);

	Point center5 = Point(2, -4, -17);
	Vector scale5 = Vector(0.5, 1.5, 1);
	Vector rot5 = Vector(0, 45, 135);
	Ellipsoid e5 = Ellipsoid(center5, scale5, rot5, brdf5);

	//Primitive* prims[5] = {&e1, &e2, &e3, &e4, &e5};
	std::vector<Primitive*> prims;
	prims.push_back(&e1);
	prims.push_back(&e2);
	prims.push_back(&e3);
	prims.push_back(&e4);
	prims.push_back(&e5);

	Scene test3 = Scene(eye, ul, ur, lr, ll, w, h,
		prims, lights);

	test3.render();
}

// room
void runtest8() {
	//Point eye = Point(6,-6,6);
	Point eye = Point(4,4,10);
	//Vector dir = Vector(-1,1,-1);
	Vector dir = Vector(-2,-2,-5);
	Vector up = proj_perp(Vector(0, 1, 0), dir);
	Point ul, ur, lr, ll;
	setview(eye, dir, up, 1, &ul, &ur, &lr, &ll);
	int w = 1000;
	int h = 1000;


	Color intensity2 = Color(1,1 , 1).scale(0.4);
	PLight light2 = PLight(intensity2, Point(6, 6, 6));
	PLight light3 = PLight(intensity2, Point(-6, -6, 6));

	std::vector<Light*> lights;
	lights.push_back(&light2);
	lights.push_back(&light3);

	float radius1 = 1;
	Point center1 = Point(0, 0, 0);
	Color ka1 = Color(0.1, 0.1, 0.1);
	//Color ka1 = Color(0, 1, 0);
	Color kd1 = Color(1, 0, 1);
	Color ks1 = Color(1, 1, 1);
	Color kr1 = Color(0, 0, 0);

	BRDF brdf1 = BRDF(kd1, ks1, ka1, kr1);

	Sphere s1 = Sphere(radius1, center1, brdf1);

	float radius2 = 1.0;
	Point center2 = Point(3, 0, 0);
	Color ka2 = Color(0.1, 0.1, 0.1);
	Color kd2 = Color(1, 1, 0);
	Color ks2 = ks1;
	Color kr2 = kr1;

	BRDF brdf2 = BRDF(kd2, ks2, ka2, kr2);
	Sphere s2 = Sphere(radius2, center2, brdf2);

	float radius3 = 1.0;
	Point center3 = Point(0, 3, 0);
	Color kd3 = Color(0, 1, 1);
	BRDF brdf3 = BRDF(kd3, ks2, ka2, kr2);
	Sphere s3 = Sphere(radius3, center3, brdf3);

	Color kat = Color(0,0,0);
	Color kdt = Color(1,1,1);
	Color kst = Color(1,1,1);
	Color krt = Color(1,1,1).scale(0);
	Color krtt = Color(1,1,1).scale(0.5);

	BRDF brdft = BRDF(kdt, kst, kat, krt);
	BRDF perf = BRDF(Color(0,0,0), kst, kat, Color(1,1,1));

	float y = -7;
	float y2 = 7;
	float b = 10000;
	Point p1 = Point(-b, y, b);
	Point p2 = Point(b, y, b);
	Point p3 = Point(0, y, -b);
	Triangle t8 = Triangle(p1, p2, p3, BRDF(Color(1,0,0), kst, kat, krtt));
	Point p4 = Point(-b, y2, b);
	Point p5 = Point(b, y2, b);
	Point p6 = Point(0, y2, -b);
	Triangle t9 = Triangle(p4, p5, p6, BRDF(Color(1,1,1), kst, kat, krt));
	float x1 = -7;
	float x2 = 7;
	Point p7 = Point(x1, -b, b);
	Point p8 = Point(x1, b, b);
	Point p9 = Point(x1, 0, -b);
	//Triangle t10 = Triangle(p7, p8, p9, BRDF(Color(0,0,1), kst, kat, krtt));
	Triangle t10 = Triangle(p7, p8, p9, BRDF(Color(0,0,1), kst, kat, krtt));
	Point pa = Point(x2, -b, b);
	Point pb = Point(x2, b, b);
	Point pc = Point(x2, 0, -b);
	Triangle tright = Triangle(pa, pb, pc, BRDF(Color(1,0.7,0), kst, kat, krt));
	float z1 = -7;
	float z2 = 7;
	Point pd = Point(-b, b, z1);
	Point pe = Point(b, b, z1);
	Point pff = Point(0, -b, z1);
	Point pg = Point(-b, b, z2);
	Point ph = Point(b, b, z2);
	Point pi = Point(0, -b, z2);
	Triangle tback = Triangle(pd,pe,pff,BRDF(Color(0,1,0), kst, kat, krt));
	//Triangle tback = Triangle(pd,pe,pff,BRDF(Color(0,0,0), kst, kat, Color(1,1,1)));
	Triangle tfront = Triangle(pg,ph,pi,brdft);

	std::vector<Primitive*> prims;
	prims.push_back(&s1);
	prims.push_back(&s2);
	prims.push_back(&s3);
	prims.push_back(&t8);
	prims.push_back(&t9);
	prims.push_back(&t10);
	prims.push_back(&tright);
	prims.push_back(&tback);
	//prims.push_back(&tfront);

	Scene test1 = Scene(eye, ul, ur, lr, ll, w, h,
		prims, lights);

	test1.render();
}


void runtest9() {
	Point eye = Point(0, 0, 0);
	Point ul = Point(-1, 1, -3);
	Point ur = Point(1, 1, -3);
	Point lr = Point(1, -1, -3);
	Point ll = Point(-1, -1, -3);
	int w = 1000;
	int h = 1000;

	float t = 1;
	Color intensity1 = Color(1, 1, 1).scale(0.6);
	Vector dir1 = Vector(t, -t, -t);
	Point pt1 = Point(0,0,0).addvec(dir1.scale(20));
	Point pt2 = Point(0,0,0).addvec(dir1.scale(-20));
	PLight plight1 = PLight(intensity1, pt1);
	PLight plight2 = PLight(intensity1, pt2);

	std::vector<Light*> lights;
	lights.push_back(&plight1);
	lights.push_back(&plight2);

	Color kau = Color(0.1, 0.1, 0.1);
	Color ksu = Color(1, 1, 1);
	Color kru = Color(0.9, 0.9, 0.9);

	Color kd1 = Color(1, 0, 0); // changed
	Color kd2 = Color(0, 1, 0);
	Color kd3 = Color(0, 0, 1);
	Color kd4 = Color(1, 1, 0);
	Color kd5 = Color(0, 1, 1);
	BRDF brdf1 = BRDF(kd1, ksu, kau, kru);
	BRDF brdf2 = BRDF(kd2, ksu, kau, kru);
	BRDF brdf3 = BRDF(kd3, ksu, kau, kru);
	BRDF brdf4 = BRDF(kd4, ksu, kau, kru);
	BRDF brdf5 = BRDF(kd5, ksu, kau, kru);

	Point center1 = Point(0, 0, -17);
	Vector scale1 = Vector(4, 2, 2);
	Vector rot1 = Vector(0, 0, 50);
	Ellipsoid e1 = Ellipsoid(center1, scale1, rot1, brdf1);

	Point center2 = Point(-2, 4, -17);
	Vector scale2 = Vector(0.5, 1.5, 1);
	Vector rot2 = Vector(0, -45, -45);
	Ellipsoid e2 = Ellipsoid(center2, scale2, rot2, brdf2);

	Point center3 = Point(-2, -4, -17);
	Vector scale3 = Vector(0.5, 1.5, 1);
	Vector rot3 = Vector(0, -45, 45);
	Ellipsoid e3 = Ellipsoid(center3, scale3, rot3, brdf3);

	Point center4 = Point(2, 4, -17);
	Vector scale4 = Vector(0.5, 1.5, 1);
	Vector rot4 = Vector(0, 45, -135);
	Ellipsoid e4 = Ellipsoid(center4, scale4, rot4, brdf4);

	Point center5 = Point(2, -4, -17);
	Vector scale5 = Vector(0.5, 1.5, 1);
	Vector rot5 = Vector(0, 45, 135);
	Ellipsoid e5 = Ellipsoid(center5, scale5, rot5, brdf5);

	//Primitive* prims[5] = {&e1, &e2, &e3, &e4, &e5};
	std::vector<Primitive*> prims;
	prims.push_back(&e1);
	prims.push_back(&e2);
	prims.push_back(&e3);
	prims.push_back(&e4);
	prims.push_back(&e5);

	Scene test3 = Scene(eye, ul, ur, lr, ll, w, h,
		prims, lights);

	test3.render();
}