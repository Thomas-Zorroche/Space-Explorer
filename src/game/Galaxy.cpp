#include "Galaxy.hpp"
#include "CelestialBody.hpp"
#include "Planet.hpp"

#include "maths/probas.hpp"

Galaxy::Galaxy(float size)
	: _celestialBodies(std::vector<CelestialBody>()), _size(size)
{
	for (size_t i = 0; i < _planetCount; i++)
	{
		int x = probas::discreteUniformDistribution(0, _size);
		int y = probas::discreteUniformDistribution(-10, 10);
		int z = probas::discreteUniformDistribution(0, _size);
		float sizePlanets = probas::continuousUniformDistribution(0.6, 6);

		std::cout << sizePlanets << std::endl;

		CelestialBody newBody = Planet(glm::vec3(x, y, z), sizePlanets);
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

