#pragma once

#include "engine/StaticMesh.hpp"
#include "glm/glm.hpp"


class CelestialBody
{
public:
	CelestialBody(const StaticMesh& mesh, glm::vec3 position);

	void draw();


private:
	glm::vec3 _position;
	StaticMesh _mesh;
	int _solarDst;
};