#ifndef COLOR_H
#define COLOR_H

#include <cmath>

class Color {
public:
	float r, g, b;
	Color();
	Color(float x, float y, float z);

	Color dot(Color a) const;
	Color scale(float f);
	void addto(Color a);
	void print();
	Color max0();
	Color min1();
};

Color::Color() {
	r = g = b = 0;
}

Color::Color(float x, float y, float z) {
	r = x;
	g = y;
	b = z;
}

Color Color::dot(Color a) const {
	return Color(r * a.r, g * a.g, b * a.b);
}

Color Color::scale(float f) {
	return Color(f*r, f*g, f*b);
}

void Color::addto(Color a) {
	r += a.r;
	g += a.g;
	b += a.b;
}

void Color::print() {
	printf("Color(%f %f %f)\n", r, g, b);
}

Color Color::max0() {
	Color ret;
	ret.r = fmax(r, 0.0f);
	ret.g = fmax(g, 0.0f);
	ret.b = fmax(b, 0.0f);
	return ret;
}

Color Color::min1() {
	Color ret;
	ret.r = fmin(r, 1.0f);
	ret.g = fmin(g, 1.0f);
	ret.b = fmin(b, 1.0f);
	return ret;
}

#endif

