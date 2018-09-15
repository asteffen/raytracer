// shuttle. runtest5
void input02() {
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
