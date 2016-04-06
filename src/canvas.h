
#ifndef __tiny_render_window__
#define __tiny_render_window__

#include "vector.h"
#include "color.h"
#include "vertex.h"
#include "mesh.h"

class Canvas {

	uint32_t *_pixels;
	double *_depth_buffer;
	int _buffer_size;

	double _width;
	double _height;

	void put_pixel(int x, int y, double z, const Color &color);
	void draw_scanline(const Vertex &v1, const Vertex &v2, int y);

public:
	Canvas(uint32_t *pixels, double width, double height) {

		_pixels = pixels;
		_width  = width;
		_height = height;
		_buffer_size  = width * height;
		_depth_buffer = new double[_buffer_size];
	};

	virtual ~Canvas() {
		delete [] _depth_buffer;
	};

	void clear();

	void draw_point(const Vector &position, const Color &color);
	void draw_line(const Vertex &v1, const Vertex &v2);
	void draw_triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3);
	void draw_mesh(const Mesh &mesh);
};

#endif
