#pragma once

#include "CelestialBody.hpp"
#include "glm/glm.hpp"
#include <vector>
#include <string>

class Planet : public CelestialBody
{
public:
	Planet(glm::vec3 position, float radius, const std::string& shaderName = "Planet");


private:
	float _radius;
	int _temperature;
	std::vector<Planet> _moons;

};