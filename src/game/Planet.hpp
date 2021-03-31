#pragma once

#include "CelestialBody.hpp"
#include "glm/glm.hpp"
#include <vector>
#include <string>

class Planet : public CelestialBody
{
public:
	Planet(glm::vec3 position, float radius, const std::string& shaderName = "Planet");

	float radius() const { return _radius; }
	const std::string& name() const { return _name; }
	
	void sendUniforms(std::shared_ptr<Shader>& shader) override;

private:
	std::string _name = "Terre";
	float _radius;
	int _temperature;
	std::vector<Planet> _moons;
	glm::vec3 _color;

};