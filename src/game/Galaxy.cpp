#include "Galaxy.hpp"
#include "CelestialBody.hpp"
#include "PlanetSettings.hpp"
#include "Planet.hpp"
#include "Sun.hpp"

#include "engine/Camera.hpp"
#include "glm/glm.hpp"
#include "hud/Hud.hpp"

#include "maths/probas.hpp"
#include "maths/utils.hpp"

Galaxy::Galaxy(float size)
	: _size(size)
{
	// First create the sun
	PlanetSettings settingSun("Sun", 8, 5505, false, randomColor(), false, true, true, 1.0, true);
	std::shared_ptr<CelestialBody> sun = std::make_shared<Sun>(glm::vec3(_size / 2.0, 0, _size / 2.0), settingSun);
	addCelestialBody(sun);

	// Then the planets
	for (size_t i = 0; i < _planetCount; i++)
	{
		int x = probas::discreteUniformDistribution(0, _size);
		int y = probas::discreteUniformDistribution(-10, 10);
		int z = probas::discreteUniformDistribution(0, _size);
		float sizePlanets = probas::continuousUniformDistribution(0.6, 6);

		PlanetSettings settingPlanet("Tatooine", sizePlanets, 40, true, randomColor(), true, true, true, 0.71);
		std::shared_ptr<CelestialBody> newBody = std::make_shared<Planet>(glm::vec3(x,y,z) , settingPlanet);
		addCelestialBody(newBody);
	}
}


void Galaxy::addCelestialBody(const std::shared_ptr<CelestialBody>& body)
{
	_celestialBodies.push_back(body);
}


void Galaxy::draw(const std::shared_ptr<Camera>& camera)
{
	bool focus = false;
	for (auto& body : _celestialBodies)
	{
		body->draw();

		// Test if user focus a planet
		auto planet = std::dynamic_pointer_cast<Planet>(body);
		if (planet)
		{
			double dot = glm::dot(camera->GetFrontVector(), glm::normalize(camera->GetPosition() - body->position()));
			if (dot < -0.98)
			{
				Hud::get().setFocusPosition(planet, camera);
				focus = true;
			}
		}
	}

	if (!focus) Hud::get().disableFocusPanel();
}

