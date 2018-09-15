// room. runtest8
void input01() {
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