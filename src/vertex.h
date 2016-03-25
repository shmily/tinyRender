#ifndef __tinyrender__vertex__
#define __tinyrender__vertex__

#include "vector.h"
#include "color.h"

class Vertex {
public:
	Vector position;
	Vector normal;
	double u;
	double v;
	Color color;

	 Vertex(const Vector &position, const Vector &normal, double u, double v, const Color &color = Color()) {
		this->position = position;
		this->normal = normal;
		this->u = u;
		this->v = v;
		this->color = color;
	};

	Vertex interpolate(const Vertex &vertex, double factor) const {
		Vector p = position.interpolate(vertex.position, factor);
		Vector n = normal.interpolate(vertex.normal, factor);
		double tu = u + (vertex.u - u) * factor;
		double tv = v + (vertex.v - v) * factor;
		Color c = color.interpolate(vertex.color, factor);

		return Vertex(p, n, tu, tv, c);
	};

};

#endif
