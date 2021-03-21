#include "Galaxy.hpp"
#include "CelestialBody.hpp"

Galaxy::Galaxy(const std::vector<CelestialBody> bodies)
	: _celestialBodies(bodies)
{

}

void Galaxy::draw()
{
	for (auto& body : _celestialBodies)
	{
		body.draw();
	}
}

