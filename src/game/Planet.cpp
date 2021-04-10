#include "Planet.hpp"
#include "maths/utils.hpp"

Planet::Planet(const glm::vec3& position, const PlanetSettings& settings)
	: CelestialBody(
	  StaticMesh(Model("res/models/planet01.obj"), 
	  TransformLayout(position, glm::vec3(0, 0, 0), settings.radius()), 
		  settings.star() ? "Sun" : "Planet"),
	  position
	  ),
	  _settings(settings)
{

}

void Planet::sendUniforms(std::shared_ptr<Shader>& shader)
{
	shader->Bind();
	shader->SetUniform3f("u_ColorPlanet", _settings.color());
	shader->Unbind();
}

