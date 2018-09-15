#include <iostream>
#include <Eigen/Dense>
#include <math.h>

const float PI = 3.14159265f;

using namespace Eigen;
using namespace std;

Matrix4f translate(Point t) {
	Matrix4f ret;
	ret << 1, 0, 0, t.x,
	       0, 1, 0, t.y,
	       0, 0, 1, t.z,
	       0, 0, 0, 1;
	return ret;
}

Matrix4f scale(Vector s) {
	Matrix4f ret;
	ret << s.x, 0, 0, 0,
	       0, s.y, 0, 0,
	       0, 0, s.z, 0,
	       0, 0, 0, 1;
	return ret;
}

Matrix4f rotatex(float t) {
	Matrix4f ret;
	float c = cos(t * PI / 180);
	float s = sin(t * PI / 180);
	ret << 1, 0, 0, 0,
	       0, c, -s, 0,
	       0, s, c, 0,
	       0, 0, 0, 1;
	return ret;
}

Matrix4f rotatey(float t) {
	Matrix4f ret;
	float c = cos(t * PI / 180);
	float s = sin(t * PI / 180);
	ret << c, 0, s, 0,
	       0, 1, 0, 0,
	       -s, 0, c, 0,
	       0, 0, 0, 1;
	return ret;
}

Matrix4f rotatez(float t) {
	Matrix4f ret;
	float c = cos(t * PI / 180);
	float s = sin(t * PI / 180);
	ret << c, -s, 0, 0,
	       s, c, 0, 0,
	       0, 0, 1, 0,
	       0, 0, 0, 1;
	return ret;
}

class Ellipsoid : public Sphere {
public:
	Matrix4f minv;
	Matrix4f minvt;
	Matrix4f m;
	Ellipsoid(Point center, Vector s, Vector r, BRDF b);

	bool intersectP(const Ray& r);
	bool intersect(const Ray& r, Point* intersection, Vector* normal);
};

Ellipsoid::Ellipsoid(Point center, Vector s, Vector r, BRDF b) {
	Matrix4f tmat = translate(center);
	//Matrix4f rmat = rotatez(r.z) * rotatey(r.y) * rotatex(r.x);
	Matrix4f rmat = rotatex(r.x) * rotatey(r.y) * rotatez(r.z);
	Matrix4f smat = scale(s);
	m = tmat * rmat * smat;
	minv = m.inverse();
	minvt = minv.transpose();
	//cout << minv << endl;

	brdf = b;
	radius = 1;
	center = Point(0, 0, 0);
}

bool Ellipsoid::intersectP(const Ray& r) {
	Vector4f vpos;
	vpos << r.pos.x, r.pos.y, r.pos.z, 1;
	Vector4f vdir;
	vdir << r.dir.x, r.dir.y, r.dir.z, 0;

	vpos = minv * vpos;
	vdir = minv * vdir;

	//cout << vdir << endl << endl;

	Point newpos = Point(vpos(0), vpos(1), vpos(2));
	Vector newdir = Vector(vdir(0), vdir(1), vdir(2));
	Ray newray = Ray(newpos, newdir, r.tmin, r.tmax);

	return Sphere::intersectP(newray);
}

bool Ellipsoid::intersect(const Ray& r, Point* intersection, Vector* normal) {
	Vector4f vpos;
	vpos << r.pos.x, r.pos.y, r.pos.z, 1;
	Vector4f vdir;
	vdir << r.dir.x, r.dir.y, r.dir.z, 0;

	vpos = minv * vpos;
	vdir = minv * vdir;

	//cout << vdir << endl << endl;

	Point newpos = Point(vpos(0), vpos(1), vpos(2));
	Vector newdir = Vector(vdir(0), vdir(1), vdir(2));
	Ray newray = Ray(newpos, newdir, r.tmin, r.tmax);

	bool ret = Sphere::intersect(newray, intersection, normal);

	Vector4f vnorm;
	vnorm << normal->x, normal->y, normal->z, 0;
	Vector4f vint;
	vint << intersection->x, intersection->y, intersection->z, 1;

	vnorm = minvt * vnorm;
	*normal = Vector(vnorm(0), vnorm(1), vnorm(2)).normalize();

	vint = m * vint;
	*intersection = Point(vint(0), vint(1), vint(2));

	return ret;
}

void etest() {
	Matrix3f m;
	m << 10, -9, -12, 7, -12, 11, -10, 10, 3;

	/*
	printmat(m);
	printmat(m.inverse());
	float a = m(2, 1); //10
	printf("%f\n", a);
	*/

	Vector3f v;
	v << 1, 2, 3;
	//std::cout << (m*v) << std::endl;

	//Ellipsoid e = Ellipsoid(Point(0, 0, 0), Vector )
}


