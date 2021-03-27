#pragma once

#include "glm/glm.hpp"
#include "engine/StaticMesh.hpp"

class Game;

class InteractiveObject
{
public:
	InteractiveObject(const StaticMesh& mesh, const glm::vec3& position)
		: _position(position), _mesh(mesh) {};

	virtual void onOverlapEvent() = 0;

	void draw() { _mesh.Draw(); }

	void disable();

	bool isActive() { return _active; }

	static void setGamePtr(Game* game) { _gamePtr = game; }

protected:
	static Game* _gamePtr;

private:

	glm::vec3 _position;
	StaticMesh _mesh;
	bool _active = true;
};