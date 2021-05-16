#pragma once

#include "engine/StaticMesh.hpp"
#include "glm/glm.hpp"
#include "PlanetSettings.hpp"

#include <memory>

class CelestialBody
{
public:
	CelestialBody(const std::shared_ptr<StaticMesh>& mesh, const glm::vec3& position, const PlanetSettings& settings);
	virtual ~CelestialBody() { _mesh->Free(); };

	void draw();

	virtual void sendUniforms(std::shared_ptr<Shader>& shader) {};
	virtual float radius() const = 0;
	virtual const std::string& name() const = 0;
	virtual const PlanetSettings& settings() const = 0;

	glm::vec3 position() const { return _position; }
	std::shared_ptr<StaticMesh> getMeshPtr() { return _mesh; }

protected:
	std::shared_ptr<StaticMesh> _mesh;
	PlanetSettings _settings;

private:
	glm::vec3 _position;
};