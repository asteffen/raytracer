#ifndef TRI_H
#define TRI_H

#include "primitive.h"

// solves system [u1 u2 u3][x] = [u4]
Vector solve_system(Vector u1, Vector u2, Vector u3, Vector u4) {
	float a, b, c, d, e, f, g, h, i, j, k, l;
	a = u1.x; b = u1.y; c = u1.z;
	d = u2.x; e = u2.y; f = u2.z;
	g = u3.x; h = u3.y; i = u3.z;
	j = u4.x; k = u4.y; l = u4.z;
	float beta, gamma, t, m;
	m = a*(e*i-h*f) + b*(g*f-d*i) + c*(d*h-e*g);
	beta = j*(e*i-h*f) + k*(g*f-d*i) + l*(d*h-e*g);
	gamma = i*(a*k-j*b) + h*(j*c-a*l) + g*(b*l-k*c);
	t = -f*(a*k-j*b) - e*(j*c-a*l) - d*(b*l-k*c);
	return Vector(beta, gamma, t).scale(1/m);
}

bool is_between(float a, float b, float c) {
	return (a <= b) && (b <= c);
}

class Triangle : public Primitive {
public:
	Point v1, v2, v3;
	Vector tnorm;
	BRDF brdf;
	int type;
	Triangle();
	Triangle(Point _v1, Point _v2, Point _v3, BRDF b);

	int gettype();
	bool intersectP(const Ray& r);
	bool intersect(const Ray& r, Point* intersection, Vector* normal);
	BRDF getBRDF();
};

Triangle::Triangle() {}

Triangle::Triangle(Point _v1, Point _v2, Point _v3, BRDF b) {
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	brdf = b;
	type = 1;

	Vector side1 = v1.sub(v2);
	Vector side2 = v1.sub(v3);
	tnorm = side1.cross(side2).normalize();
}

int Triangle::gettype() {
	return type;
}

BRDF Triangle::getBRDF() {
	return brdf;
}

bool Triangle::intersectP(const Ray& r) {
	Point e = r.pos;
	Vector d = r.dir;

	Vector u1 = v1.sub(v2);
	Vector u2 = v1.sub(v3);
	Vector u3 = d;
	Vector u4 = v1.sub(e);

	Vector ans = solve_system(u1, u2, u3, u4);
	float beta, gamma, t;
	beta = ans.x;
	gamma = ans.y;
	t = ans.z;

	if (!r.inrange(t)) return false;
	if (!is_between(0, gamma, 1)) return false;
	if (!is_between(0, beta, 1-gamma)) return false;
	return true;
}

bool Triangle::intersect(const Ray& r, Point* intersection, Vector* normal) {
	Point e = r.pos;
	Vector d = r.dir;

	Vector u1 = v1.sub(v2);
	Vector u2 = v1.sub(v3);
	Vector u3 = d;
	Vector u4 = v1.sub(e);

	Vector ans = solve_system(u1, u2, u3, u4);

	float beta, gamma, t;
	beta = ans.x;
	gamma = ans.y;
	t = ans.z;

	if (!r.inrange(t)) return false;
	if (!is_between(0, gamma, 1)) return false;
	if (!is_between(0, beta, 1-gamma)) return false;
	//ans.print();
	
	*intersection = r.pos.addvec(r.dir.scale(t));
	//*normal = tnorm.scale(-1);

	float dotp = r.dir.dot(tnorm);
	if (dotp > 0) {
		*normal = tnorm;
	} else {
		*normal = tnorm.scale(-1);
	}
	*normal = (*normal).scale(-1);
	
	return true;
}


#endif

