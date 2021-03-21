#pragma once

#include <vector>

class CelestialBody;

class Galaxy
{
public:
	Galaxy(const std::vector<CelestialBody> bodies);

	void draw();

private:
	std::vector<CelestialBody> _celestialBodies;
};