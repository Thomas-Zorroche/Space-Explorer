#include "Planet.hpp"
#include "maths/utils.hpp"

Planet::Planet(glm::vec3 position, float radius, const std::string& shaderName)
	: CelestialBody(
	  StaticMesh(Model("res/models/planet01.obj"), TransformLayout(position, glm::vec3(0, 0, 0), radius), shaderName),
	  position
	  ),
	  _radius(radius), _color(randomColor(0.25))
{

}

void Planet::sendUniforms(std::shared_ptr<Shader>& shader)
{
	shader->Bind();
	shader->SetUniform3f("u_ColorPlanet", _color);
	shader->Unbind();
}

