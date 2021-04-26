#include "Sun.hpp"
#include "maths/utils.hpp"

Sun::Sun(const glm::vec3& position, const PlanetSettings& settings)
	: CelestialBody(
		std::make_shared<StaticMesh>(std::make_shared<Model>(), TransformLayout(position, glm::vec3(0), settings.radius()), "Sun")
		, position),
	_settings(settings)
{

}

void Sun::sendUniforms(std::shared_ptr<Shader>& shader)
{
	shader->Bind();
	shader->SetUniform3f("u_ColorPlanet", _color);
	shader->Unbind();
}

