#pragma once

#include <vector>
#include <memory>

class Camera;
class CelestialBody;

class Galaxy
{
public:
	Galaxy(float size);

	void draw(const std::shared_ptr<Camera>& camera);

private:
	void addCelestialBody(const CelestialBody& body);

private:
	std::vector<CelestialBody> _celestialBodies;
	
	int _planetCount = 10;
	int _size = 100;
};