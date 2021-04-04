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

	std::vector<std::shared_ptr<CelestialBody> > celestialBodies() { return _celestialBodies; }

private:
	void addCelestialBody(const std::shared_ptr<CelestialBody>& body);

private:
	std::vector<std::shared_ptr<CelestialBody> > _celestialBodies;
	
	int _planetCount = 10;
	int _size = 100;
};