#pragma once

#include "CelestialBody.hpp"
#include "proceduralPlanet/Planet.hpp"

#include "glm/glm.hpp"
#include <vector>
#include <string>
#include <memory>

class Planet : public CelestialBody
{
public:
	Planet(const glm::vec3& position, const PlanetSettings& settings);

	void sendUniforms(std::shared_ptr<Shader>& shader) override;
	float radius() const override { return _settings.radius(); }
	const std::string& name() const override { return _settings.name(); }
	const PlanetSettings& settings() const override { return _settings; }

private:
	std::shared_ptr<proceduralPlanet::Planet> _proceduralPlanet;
};
