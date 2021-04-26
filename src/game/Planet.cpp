#include "Planet.hpp"
#include "maths/utils.hpp"
#include "proceduralPlanet/Planet.hpp"
#include "proceduralPlanet/io/IOManager.hpp"

Planet::Planet(const glm::vec3& position, const PlanetSettings& settings)
	: CelestialBody(proceduralPlanet::Planet(1).GetStaticMesh(), position),
	_proceduralPlanet(std::make_shared<proceduralPlanet::Planet>(64)),
	_settings(settings)
{
	proceduralPlanet::IOManager::get().open("res/planets/InitPlanet.ini", _proceduralPlanet);
	_proceduralPlanet->RandomGenerate();
	_mesh = _proceduralPlanet->GetStaticMesh();
	_mesh.Translate(position);
	_mesh.Scale(settings.radius());
}

void Planet::sendUniforms(std::shared_ptr<Shader>& shader)
{
	shader->Bind();
	_proceduralPlanet->sendUniforms(shader);
	shader->Unbind();
}

