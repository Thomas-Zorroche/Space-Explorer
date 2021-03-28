#pragma once

#include "game/Planet.hpp"
#include "glm/glm.hpp"

class Sun : public Planet
{
public:
	Sun(const glm::vec3& position, float size)
		: Planet(position, size, "Sun") {}
};