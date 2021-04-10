#pragma once

#include "game/Planet.hpp"
#include "game/PlanetSettings.hpp"
#include "glm/glm.hpp"

class Sun : public Planet
{
public:
	Sun(const glm::vec3& position, const PlanetSettings& setting)
		: Planet(position, setting) {}
};