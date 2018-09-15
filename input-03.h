// ellipsoids. runtest9
void input03() {
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