#ifndef __tinyrender__mesh__
#define __tinyrender__mesh__

#include <vector>
#include "vertex.h"

class Mesh {
public:
	Vector position;
	Vector rotation;
	Vector scale;

	std::vector<Vertex> vertices;
	std::vector<int> indices;

	Mesh() {
		position = Vector(0, 0, 0);
		rotation = Vector(0, 0, 0);
		scale    = Vector(1, 1, 1);
    };

	Mesh(const char *path, const char *texturePath);

	virtual ~Mesh() {
	};
};

#endif
