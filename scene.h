#ifndef SCENE_H
#define SCENE_H

#include <cfloat>
#include <cmath>
#include "color.h"
#include "light.h"
#include "point.h"
#include "primitive.h"
#include "pngpp/png.hpp"

#define DEBUG 0
#define LAYERTEST 0

// specular constant
const float SPV = 50.0;

// epsilon for shadow rays
const float EPSILON = 1e-2;

// recursion depth for reflections
const int RECURSION_DEPTH = 5;

class Scene {
public:
	Point eye;
	Point ul, ur, lr, ll;
	int w, h;
	std::vector<Primitive*> primitives;
	int num_prims;
	std::vector<Light*> lights;
	int num_lights;

	Scene();

	Scene(Point _eye, Point _ul, Point _ur, Point _lr, Point _ll,
		int _w, int _h, std::vector<Primitive*> _primitives,
		std::vector<Light*> _lights);

	Ray pixel2ray(int x, int y);

	void trace(Ray ray, int depth, Color* color);

	void shading(Color* color, const BRDF& brdf, const Vector& normal,
		const Vector& view, const Vector& lray, const Color& intensity);

	void render();

	bool rayhitsanything(const Ray& ray);
};

Scene::Scene() {
}

Scene::Scene(Point _eye, Point _ul, Point _ur, Point _lr, Point _ll,
	int _w, int _h, std::vector<Primitive*> _primitives,
	std::vector<Light*> _lights) {
	eye = _eye;
	ul = _ul;
	ur = _ur;
	lr = _lr;
	ll = _ll;
	w = _w;
	h = _h;
	primitives = _primitives;
	num_prims = primitives.size();
	lights = _lights;
	num_lights = lights.size();
}

Ray Scene::pixel2ray(int x, int y) {
	float u = ((float) x) / w;
	float v = ((float) y) / h;
	//printf("u= %f\n", u);

	Point p1 = ll.scale(v).add(ul.scale(1-v));
	Point p2 = lr.scale(v).add(ur.scale(1-v));
	Point p = p1.scale(u).add(p2.scale(1-u));

	Vector dir = p.sub(eye);
	return Ray(eye, dir, 1, FLT_MAX);
}

void Scene::trace(Ray ray, int depth, Color* color) {
	if (depth > RECURSION_DEPTH) {
		//*color = Color(0, 0, 0);
		return;
	}

	// loop through primitives
	for (int p = 0; p < num_prims; p++) {
		Point intersection;
		Vector normal;
		bool hits = primitives[p]->intersect(ray, &intersection, &normal);
		if (!hits) continue;

		//bool ist = false;
		if (DEBUG && (primitives[p]->gettype()) == 1) {
			normal.print();
			//ist = true;
		}

		Vector view = intersection.sub(ray.pos).normalize();
		BRDF brdf = primitives[p]->getBRDF();
		Ray overlap_ray = Ray(intersection, ray.pos.sub(intersection),
			EPSILON, 1-EPSILON);

		bool overlapped = rayhitsanything(overlap_ray);

		// if overlapped, don't need to check mirror reflection either.
		if (overlapped) continue;

		// ambient added only once, not in reflections.
		if ((depth == 0) || LAYERTEST) {
			//color->addto(brdf.ka.dot(intensity));
			color->addto(brdf.ka);
		}

		// there is an intersection, loop through light sources
		for (int l = 0; l < num_lights; l++) {
			Color intensity = lights[l]->getIntensity();
			Vector lray = lights[l]->getDir(intersection);
			float tmax = lights[l]->getTmax(intersection);

			Ray shadow_ray = Ray(intersection, lray.scale(-1), EPSILON, tmax);

			if (!rayhitsanything(shadow_ray)) {
			//if (1) {
				shading(color, brdf, normal, view, lray, intensity);
			}
		}

		// handle mirror reflection
		if (brdf.kr.r > 0 || brdf.kr.g > 0 || brdf.kr.b > 0) {
			Vector l = view.scale(-1);
			float cosine = l.dot(normal);
			Vector ref = l.scale(-1).add(normal.scale(2*cosine));

			Ray reflect_ray = Ray(intersection, ref, EPSILON, FLT_MAX);

			if (1) {
				Color tempColor = Color(0, 0, 0);
				trace(reflect_ray, depth+1, &tempColor);
				color->addto(brdf.kr.dot(tempColor));
			}
		}
	}
}

bool Scene::rayhitsanything(const Ray& ray) {
	for (int p = 0; p < num_prims; p++) {
		bool hits = primitives[p]->intersectP(ray);
		if (hits) return true;
	}
	return false;
}

void Scene::shading(Color* color, const BRDF& brdf, const Vector& normal,
	const Vector& view, const Vector& lray, const Color& intensity) {

	// diffuse. lraym is negative version
	Vector lraym = lray.scale(-1);
	float cosinem = lraym.dot(normal);
	color->addto(brdf.kd.dot(intensity).scale(cosinem).max0());

	// specular.
	float cosine = lray.dot(normal);

	Vector refl = lray.scale(-1).add(normal.scale(2*cosine));
	float pwr = pow(fmax(refl.dot(view), 0), SPV);
	color->addto(brdf.ks.dot(intensity).scale(pwr));

	// ambient
	//color->addto(brdf.ka.dot(intensity));
}

void Scene::render() {
	png::image<png::rgb_pixel> image(w, h);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x) {
			Ray ray = pixel2ray(x, y);

			Color color = Color(0, 0, 0);
			trace(ray, 0, &color);

			// make sure color is between 0 and 1, then multiply by 255
			color = color.max0().min1().scale(255);

			// flip in x-dir to match output
			image[y][w-1-x] = png::rgb_pixel(color.r, color.g, color.b);
		}
	}
	image.write("output.png");
}



#endif
