#include "game/CelestialBody.hpp"

CelestialBody::CelestialBody(const StaticMesh& mesh, glm::vec3 position)
	: _mesh(mesh), _position(position), _solarDst(0)
{
	_mesh.Translate(position);
}

void CelestialBody::draw() 
{
	sendUniforms(_mesh.GetShader());
	_mesh.Draw();
}

