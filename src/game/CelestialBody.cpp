#include "game/CelestialBody.hpp"

CelestialBody::CelestialBody(const std::shared_ptr<StaticMesh>& mesh, const glm::vec3& position, const PlanetSettings& settings)
	: _mesh(mesh), _position(position), _settings(settings)
{

}

void CelestialBody::draw() 
{
	sendUniforms(_mesh->GetShader());
	_mesh->Draw();
}

