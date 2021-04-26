#include "game/CelestialBody.hpp"

CelestialBody::CelestialBody(const std::shared_ptr<StaticMesh>& mesh, const glm::vec3& position)
	: _mesh(mesh), _position(position), _solarDst(0)
{
	if (_mesh)
		_mesh->Translate(position);
}

void CelestialBody::draw() 
{
	sendUniforms(_mesh->GetShader());
	_mesh->Draw();
}

