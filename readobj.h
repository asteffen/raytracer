#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include "triangle.h"

using namespace std;

#define DEBUG_OBJ 0

// reads until space
string getword(string line, int* pos) {
	string ret;
	char c;
	int i = *pos;
	for (; i < line.length(); i++) {
		c = line.at(i);
		if (c == ' ') {
			// skip extra spaces
			while (i < line.length() && line.at(i) == ' ') i++;
			break;
		}
		ret += c;
	}
	
	*pos = i;
	return ret;
}

void readobj(char* filename, std::vector<Primitive*>* prims, BRDF b) {
	ifstream file(filename);
	string line;

	std::vector<Point> pts;
	

	// to get indices aligned
	pts.push_back(Point(0,0,0));

	while (getline(file, line)) {
		int pos = 0;
		string start = getword(line, &pos);
		//if (start == "#" || start == "") continue;

		string w1 = getword(line, &pos);
		string w2 = getword(line, &pos);
		string w3 = getword(line, &pos);
		string w4 = getword(line, &pos);

		if (start == "v") {
			float f1 = atof(w1.c_str());
			float f2 = atof(w2.c_str());
			float f3 = atof(w3.c_str());
			//printf("%f\n", f);
			Point p = Point(f1, f2, f3);
			pts.push_back(p);
		} else if (start == "f") {
			int f1 = atoi(w1.c_str());
			int f2 = atoi(w2.c_str());
			int f3 = atoi(w3.c_str());
			int f4 = atoi(w4.c_str());
			//printf("%d\n", f1);
			//Triangle t = Triangle(pts[f1], pts[f2], pts[f3], b);
			//prims.push_back(&t);
			Triangle *t = new Triangle(pts[f1], pts[f2], pts[f3], b);
			prims->push_back(t);

			//quadrilateral
			if (w4 != "") {
				t = new Triangle(pts[f1], pts[f3], pts[f4], b);
				prims->push_back(t);
			}
		}

		//char next = line.at(pos);

		if (DEBUG_OBJ) printf("start=<%s>, w1=<%s>, w2=<%s>, w4=<%s>\n",
			start.c_str(), w1.c_str(), w2.c_str(), w4.c_str());
	}
	//pts[0].print();
	//pts[1].print();

}

void setview(Point eye, Vector dir, Vector up, float ratio,
	Point* ul, Point *ur, Point* lr, Point* ll) {
	dir = dir.normalize();
	up = up.normalize();
	Point viewcen = eye.addvec(dir.scale(ratio));
	Vector right = dir.cross(up);
	*ul = viewcen.addvec(up).subvec(right);
	*ur = viewcen.addvec(up).addvec(right);
	*lr = viewcen.subvec(up).addvec(right);
	*ll = viewcen.subvec(up).subvec(right);
}

Vector proj(Vector a, Vector b) {
	float r = a.dot(b) / b.dot(b);
	return b.scale(r);
}

Vector proj_perp(Vector a, Vector b) {
	return a.sub(proj(a,b));
}

