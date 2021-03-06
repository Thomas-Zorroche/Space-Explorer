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

Galaxy::Galaxy(float size, GLFWwindow* window)
	: _size(size)
{
	// First create the sun
	PlanetSettings settingSun("Sun", 8, 5505, false, randomColor(), false, true, true, 1.0, true);
	std::shared_ptr<CelestialBody> sun = std::make_shared<Sun>(glm::vec3(_size / 2.0, 0, _size / 2.0), settingSun);
	addCelestialBody(sun);

	Hud::get().displayLoadingWindow(0, window);
	// Then the planets
	for (size_t i = 0; i < _planetCount; i++)
	{
		int x = probas::continuousUniformDistribution(0, size);
		int y = probas::continuousUniformDistribution(-probas::simulatePoissonProb(3), probas::simulatePoissonProb(12));
		int z = probas::continuousUniformDistribution(0, size);

		PlanetSettings settingPlanet = PlanetSettings::generatePlanetSettings(glm::distance(glm::vec3(size / 2), glm::vec3(x, y, z)));
		std::shared_ptr<CelestialBody> newBody = std::make_shared<Planet>(glm::vec3(x,y,z) , settingPlanet);
		addCelestialBody(newBody);

		Hud::get().displayLoadingWindow(i / (float)_planetCount, window);
	}

	Hud::get().displayLoadingWindow(1, window);
}


void Galaxy::addCelestialBody(const std::shared_ptr<CelestialBody>& body)
{
	_celestialBodies.push_back(body);
}


void Galaxy::draw(const std::shared_ptr<Camera>& camera)
{
	bool focus = false;
	float dstFocus = 1000000.0f;
	for (auto& body : _celestialBodies)
	{
		// Focus planet
		double dot = glm::dot(camera->GetFrontVector(), glm::normalize(camera->GetPosition() - body->position()));
		float dstPlanet = distanceSqr(camera->GetPosition(), body->position());
		if (dot < -0.99 && dstPlanet < dstFocus)
		{
			Hud::get().setFocusPosition(body, camera);
			focus = true;
			dstFocus = dstPlanet;
		}

		// Spin planet
		auto meshPtr = body->getMeshPtr();
		meshPtr->Rotate(glm::vec3(0, 0.03, 0));

		body->draw();
	}

	if (!focus) Hud::get().disableFocusPanel();
}

