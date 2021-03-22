#pragma once

#include <vector>

class CelestialBody;

class Galaxy
{
public:
	Galaxy();

	void draw();

private:
	void addCelestialBody(const CelestialBody& body);

private:
	std::vector<CelestialBody> _celestialBodies;
	
	int _planetCount = 10;
	int _radius = 100;
};