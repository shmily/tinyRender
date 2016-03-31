
#include <stdio.h>
#include <vector>
#include "mesh.h"
#include "rply/rply.h"

static int vertex_callback(p_ply_argument argument) {
	static double point[3];
	void *mesh;
	long index;

	ply_get_argument_user_data(argument, &mesh, &index);
	point[index] = ply_get_argument_value(argument);

	if (index == 2) {
		Vector p(point[0], point[1], point[2]);
		Vector n;
		Vertex vertex(p, n, 0.0, 0.0);
		static_cast<Mesh *>(mesh)->vertices.push_back(vertex);
	}

	return 1;
}

static int triangle_callback(p_ply_argument argument) {
	static int triangle[3];
	void *mesh;
	long index;

	ply_get_argument_user_data(argument, &mesh, NULL);
	ply_get_argument_property(argument, NULL, NULL, &index);
	triangle[index] = ply_get_argument_value(argument);

	if (index == 2) {
		static_cast<Mesh *>(mesh)->indices.push_back(triangle[0]);
		static_cast<Mesh *>(mesh)->indices.push_back(triangle[1]);
		static_cast<Mesh *>(mesh)->indices.push_back(triangle[2]);
	}

	return 1;
}

Mesh::Mesh(const char *path, const char *texturepath) {

	position = Vector(0, 0, 0);
	rotation = Vector(0, 0, 0);
	scale    = Vector(1, 1, 1);

	p_ply ply = ply_open(path, NULL, 0, NULL);
	if (!ply) return;
	if (!ply_read_header(ply)) return;

	ply_set_read_cb(ply, "vertex", "x", vertex_callback, this, 0);
	ply_set_read_cb(ply, "vertex", "y", vertex_callback, this, 1);
	ply_set_read_cb(ply, "vertex", "z", vertex_callback, this, 2);
	ply_set_read_cb(ply, "face", "vertex_indices", triangle_callback, this, 0);

	ply_read(ply);
	ply_close(ply);

	printf("total vertex  : %ld\n", vertices.size());
	printf("total triangle: %ld\n", indices.size() / 3);
	return;
}
