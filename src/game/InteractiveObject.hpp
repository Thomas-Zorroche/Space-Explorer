#pragma once

#include "glm/glm.hpp"
#include "engine/StaticMesh.hpp"

class Game;

class InteractiveObject
{
public:
	InteractiveObject(const StaticMesh& mesh, const glm::vec3& position, float velocity)
		: _position(position), _mesh(mesh), _velocity(velocity) {};

	virtual void onOverlapEvent() = 0;

	void draw();

	void disable();

	bool isActive() { return _active; }

	static void setGamePtr(Game* game) { _gamePtr = game; }

protected:
	static Game* _gamePtr;

private:
	float _velocity;
	glm::vec3 _position;
	StaticMesh _mesh;
	bool _active = true;
};