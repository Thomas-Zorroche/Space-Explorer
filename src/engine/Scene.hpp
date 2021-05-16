#pragma once

#include <vector>
#include <memory>
#include <string>
#include "glm/glm.hpp"

#include "game/Game.hpp"

class StaticMesh;
class Skybox;
class Galaxy;
class InteractiveObject;
class Camera;

class Scene
{
public:
	Scene(float size, const Game& game);
	~Scene();

	void Init();

	void Draw(const std::shared_ptr<Camera>& camera, const Game& game);

	std::shared_ptr<StaticMesh>& StaticMeshPtr(int index) { return _staticMeshes[index]; }

	void Free();

	float size() const { return _size; }

	void LoadHints(const Game& game);

private:
	void AddStaticMesh(const std::shared_ptr<StaticMesh>& mesh);

private:
	std::vector<std::shared_ptr<StaticMesh> > _staticMeshes;
	std::vector<std::shared_ptr<InteractiveObject> > _interactiveObjects = std::vector<std::shared_ptr<InteractiveObject> >();
	std::shared_ptr<Skybox> _skybox;
	std::shared_ptr<Galaxy> _galaxy;

	unsigned int _staticMeshesCount = 0;
	float _size = 1000.0f;
};

