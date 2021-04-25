#pragma once

#include "CelestialBody.hpp"
#include "PlanetSettings.hpp"

#include "glm/glm.hpp"
#include <vector>
#include <string>

class Planet : public CelestialBody
{
public:
	Planet(const glm::vec3& position, const PlanetSettings& settings);

	void sendUniforms(std::shared_ptr<Shader>& shader) override;

	float radius() const { return _settings.radius(); }
	const std::string& name() const { return _settings.name(); }

	const PlanetSettings& settings() const { return _settings; }

private:
	PlanetSettings _settings;

	//std::vector<Planet> _moons;

};
