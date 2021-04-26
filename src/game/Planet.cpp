#include "Planet.hpp"
#include "maths/utils.hpp"
#include "proceduralPlanet/Planet.hpp"

Planet::Planet(const glm::vec3& position, const PlanetSettings& settings)
	: CelestialBody(proceduralPlanet::Planet(50).GetStaticMesh(), position),
	_proceduralPlanet(12),
	_settings(settings)
{
	_proceduralPlanet.RandomGenerate();
}

void Planet::sendUniforms(std::shared_ptr<Shader>& shader)
{
	shader->Bind();
	_proceduralPlanet.sendUniforms(shader);
	shader->Unbind();
}

