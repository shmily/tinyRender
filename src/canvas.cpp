
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <vector>

#include "canvas.h"

void
Canvas::put_pixel(int x, int y, double z, const Color &color) {
	int index = _width * y + x;
	double depth = _depth_buffer[index];

	if (depth < z) {
		return;
	}

	_depth_buffer[index] = z;
	_pixels[index] = color.uint32();
}

void
Canvas::draw_scanline(const Vertex &v1, const Vertex &v2, int y) {
	int x1 = v1.position.x;
	int x2 = v2.position.x;
	int sign = x2 > x1 ? 1 : -1;
	double factor = 0.0;

	for (int x = x1, i = 0; i < (x2-x1) * sign + 1; i++, x += sign) {
		if (x1 != x2)
			factor = (double)(x - x1) / (x2 - x1);

		auto v = v1.interpolate(v2, factor);
		draw_point(v.position, Color::randomColor());
	}
}

void
Canvas::clear() {
	memset(_pixels, 0, sizeof(uint32_t) * _width * _height);
	std::fill(_depth_buffer, _depth_buffer + _buffer_size, DBL_MAX);
}

void
Canvas::draw_point(const Vector &position, const Color &color) {
	if (position.x >= 0 && position.y >= 0 &&
		position.x < _width && position.x < _height) {

		put_pixel(position.x, position.y, position.z, color);
	}
}

void
Canvas::draw_line(const Vertex &v1, const Vertex &v2) {
	int x1 = v1.position.x;
	int y1 = v1.position.y;
	int x2 = v2.position.x;
	int y2 = v2.position.y;

	int dx = x2 - x1;
	int dy = y2 - y1;

	if (abs(dx) > abs(dy)) {
		int sign = dx > 0 ? 1 : -1;
		double ratio = 0;

		if (dx != 0)
			ratio = (double)dy / dx;

		for (int x = x1; x != x2; x += sign) {
			int y = y1 + (x - x1) * ratio;
			Color c = v1.color + (v2.color - v1.color) * ((double)(x - x1) / (x2 - x1));
			draw_point(Vector(x, y), c);
		}
	} else {
		int sign = dy > 0 ? 1 : -1;
		double ratio = 0;

		if (dy != 0)
			ratio = (double)dx / dy;

		for (int y = y1; y != y2; y += sign) {
			int x = x1 + (y - y1) * ratio;
			Color c = v1.color + (v2.color - v1.color) * ((double)(y - y1) / (y2 -y1));
			draw_point(Vector(x, y), c);
		}
	}
}

void
Canvas::draw_triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
	const Vertex *a = &v1;
	const Vertex *b = &v2;
	const Vertex *c = &v3;

	if (a->position.y > b->position.y)
		std::swap(a, b);
	if (b->position.y > c->position.y)
		std::swap(b,c);
	if (a->position.y > b->position.y)
		std::swap(a, b);

	double middle_factor = (double)(b->position.y - a->position.y) / (c->position.y - a->position.y);
	Vertex middle = a->interpolate(*c, middle_factor);

	int start_y = a->position.y;
	int end_y   = b->position.y;
	for (int y = start_y; y <= end_y; ++y) {
		double factor = 0;
		if (end_y != start_y)
			factor = (double)(y - start_y) / (end_y - start_y);

		Vertex va = a->interpolate(*b, factor);
		Vertex vb = a->interpolate(middle, factor);
		draw_scanline(va, vb, y);
	}
#if 0
	start_y = b->position.y;
	end_y   = c->position.y;
	for (int y = start_y; y <= end_y; ++y) {
		double factor = 0;
		if (end_y != start_y)
			factor = (double)(y - start_y) / (end_y - start_y);

		Vertex va = b->interpolate(*c, factor);
		Vertex vb = middle.interpolate(*c, factor);
		va.position.y = vb.position.y = y;
		draw_scanline(va, vb, y);
	}
#else
	start_y = c->position.y;
	end_y   = b->position.y;
	for (int y = start_y; y >= end_y; --y) {
		double factor = 0;
		if (end_y != start_y)
			factor = (double)(start_y - y) / (start_y - end_y);

		Vertex va = c->interpolate(*b, factor);
		Vertex vb = c->interpolate(middle, factor);
		draw_scanline(va, vb, y);
	}
#endif
}

void
Canvas::draw_mesh(const Mesh &mesh) {

}
