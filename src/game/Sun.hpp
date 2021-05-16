#pragma once

#include "CelestialBody.hpp"

#include "glm/glm.hpp"
#include <vector>
#include <string>
#include <memory>

class Sun : public CelestialBody
{
public:
	Sun(const glm::vec3& position, const PlanetSettings& settings);

	void sendUniforms(std::shared_ptr<Shader>& shader) override;
	float radius() const override { return _settings.radius(); }
	const std::string& name() const override { return _settings.name(); }
	const PlanetSettings& settings() const override { return _settings; }

private:
	glm::vec3 _color;
};
