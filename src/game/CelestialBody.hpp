#pragma once

#include "engine/StaticMesh.hpp"
#include "glm/glm.hpp"


class CelestialBody
{
public:
	CelestialBody(const StaticMesh& mesh, glm::vec3 position);
	virtual ~CelestialBody() { _mesh.Free(); };

	void draw();
	virtual void sendUniforms(std::shared_ptr<Shader>& shader) {};

	glm::vec3 position() const { return _position; }

protected:
	StaticMesh _mesh;

private:
	glm::vec3 _position;
	int _solarDst;
};