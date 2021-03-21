#pragma once

#include "CelestialBody.hpp"
#include "glm/glm.hpp"
#include <vector>

class Planet : public CelestialBody
{
public:
	Planet(glm::vec3 position, float radius);

private:
	float _radius;
	int _temperature;
	std::vector<Planet> _moons;

};