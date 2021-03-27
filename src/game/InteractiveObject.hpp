#pragma once

#include "glm/glm.hpp"
#include "engine/StaticMesh.hpp"


class InteractiveObject
{
public:
	InteractiveObject(const StaticMesh& mesh, const glm::vec3& position)
		: _position(position), _mesh(mesh) {};

	virtual void onOverlapEvent() = 0;

	void draw() { _mesh.Draw(); }

	void disable() 
	{ 
		_active = false;
		_mesh.disableBoundingBox();
	}

	bool isActive() { return _active; }

private:
	glm::vec3 _position;
	StaticMesh _mesh;
	bool _active = true;
};