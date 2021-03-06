#include "Planet.hpp"
#include "maths/utils.hpp"
#include "proceduralPlanet/Planet.hpp"
#include "proceduralPlanet/io/IOManager.hpp"

Planet::Planet(const glm::vec3& position, const PlanetSettings& settings)
	: CelestialBody(nullptr, position, settings),
	_proceduralPlanet(std::make_shared<proceduralPlanet::Planet>(120, TransformLayout(position, glm::vec3(0), settings.radius())))
{
	proceduralPlanet::IOManager::get().open("res/planets/InitPlanet.ini", _proceduralPlanet);
	_mesh = _proceduralPlanet->GetStaticMesh();
}

void Planet::sendUniforms(std::shared_ptr<Shader>& shader)
{
	shader->Bind();
	_proceduralPlanet->sendUniforms(shader);
	shader->Unbind();
}

