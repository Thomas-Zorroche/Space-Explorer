#pragma once

#include <vector>

class CelestialBody;

class Galaxy
{
public:
	Galaxy(float size);

	void draw();

private:
	void addCelestialBody(const CelestialBody& body);

private:
	std::vector<CelestialBody> _celestialBodies;
	
	int _planetCount = 10;
	int _size = 100;
};