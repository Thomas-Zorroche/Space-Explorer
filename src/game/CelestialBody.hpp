#pragma once

#include "engine/StaticMesh.hpp"
#include "glm/glm.hpp"

#include <memory>

class CelestialBody
{
public:
	CelestialBody(const std::shared_ptr<StaticMesh>& mesh, const glm::vec3& position);
	virtual ~CelestialBody() { _mesh->Free(); };

	void draw();
	virtual void sendUniforms(std::shared_ptr<Shader>& shader) {};

	glm::vec3 position() const { return _position; }

	std::shared_ptr<StaticMesh> getMeshPtr() { return _mesh; }

protected:
	std::shared_ptr<StaticMesh> _mesh;

private:
	glm::vec3 _position;
	int _solarDst;
};