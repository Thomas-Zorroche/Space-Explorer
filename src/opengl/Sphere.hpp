#pragma once

#include <vector>
#include "common.hpp"

class Sphere
{
public:
	Sphere(float radius = 1.0f, int rings = 12, int sector = 24);

	const std::vector<ShapeVertex> vertices() const {
		return _vertices;

	}
	GLsizei vertexCount() const {
		return _nVertexCount;
	}

private:
	void build(float radius, int rings, int sector);

	std::vector<ShapeVertex> _vertices;
	GLsizei _nVertexCount;
};