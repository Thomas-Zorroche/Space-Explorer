#pragma once

#include "collision/BoundingSphere.hpp"
#include "collision/CollisionGrid.hpp"
#include "engine/Camera.hpp"

#include <vector>
#include <memory>
#include <unordered_map>

class Camera;

class CollisionManager
{
public:
	CollisionManager();

	void CheckCollisions();
	void AddSphere(const std::shared_ptr<BoundingSphere>& sphere);
	void DeleteSphere(const std::shared_ptr<BoundingSphere>& sphere);

	void SetCamera(const std::shared_ptr<Camera>& cameraPtr) { _camera = cameraPtr; }

	void debugMode();

private:
	void updateCaseIndices(const CollisionGridCase& gridCase, int indexDeadBox);

	CollisionGrid _grid;
	std::unordered_map<CollisionGridCase, std::vector<std::shared_ptr<BoundingSphere> >> _spheres;
	std::shared_ptr<Camera> _camera;

	bool _debugMode = false;
};