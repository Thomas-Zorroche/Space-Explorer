#include "Galaxy.hpp"
#include "CelestialBody.hpp"
#include "Planet.hpp"

#include "maths/probas.hpp"

Galaxy::Galaxy()
	: _celestialBodies(std::vector<CelestialBody>())
{
	for (size_t i = 0; i < _planetCount; i++)
	{
		int x = probas::discreteUniformDistribution(-_radius, _radius);
		int y = probas::discreteUniformDistribution(-5, 5);
		int z = probas::discreteUniformDistribution(-_radius, _radius);
		int size = probas::continuousUniformDistribution(0.5, 6);

		std::cout << x << " " << y << " " << z << std::endl;

		CelestialBody newBody = Planet(glm::vec3(x, y, z), size);
		addCelestialBody(newBody);
	}
}


void Galaxy::addCelestialBody(const CelestialBody& body)
{
	_celestialBodies.push_back(body);
}


void Galaxy::draw()
{
	for (auto& body : _celestialBodies)
	{
		body.draw();
	}
}

