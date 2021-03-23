#include "CollisionManager.hpp"
#include "collision/CollisionGrid.hpp"
#include "collision/BoundingSphere.hpp"

CollisionManager::CollisionManager()
{
	for (size_t i = (size_t)0; i < (size_t)_grid.Resolution(); i++)
	{
		for (size_t j = (size_t)0; j < (size_t)_grid.Resolution(); j++)
		{
			_spheres.insert({
				CollisionGridCase(i, j),
				std::vector<std::shared_ptr<BoundingSphere> >()
				});
		}
	}
}

void CollisionManager::CheckCollisions()
{
	// Retrieve all active boxes from the current grid case where the player is moving
	glm::vec3 cameraPosition = _camera->GetPosition();
	CollisionGridCase playerCase = _grid.getCase(cameraPosition);
	auto& activeSpheres = _spheres[playerCase];

	// Check all collisions between spheres and camera
	int countCollision = 0;
	for (size_t i = (size_t)0; i < activeSpheres.size(); i++)
	{
		//std::cout << "SPHERE" << activeSpheres[i]->center().x << " " << activeSpheres[i]->center().z << std::endl;

		bool hit = activeSpheres[i]->isPointInsideSphere(cameraPosition);
		
		// If colliding, execute appropriate event
		if (hit)
		{
			if (activeSpheres[i]->StopPlayerMovement())
				_camera->BlockMovement();

			activeSpheres[i]->onBeginOverlap();
			countCollision++;
		}
	}
}

void CollisionManager::AddSphere(const std::shared_ptr<BoundingSphere>& sphere)
{
	// Retrive case coordinates of the box
	CollisionGridCase sphereCase = _grid.getCase(sphere);

	// Add it to the right vector
	_spheres[sphereCase].push_back(sphere);
	sphere->AddIndex(sphereCase, _spheres[sphereCase].size() - 1);

	// Check whether the box is close to others boxes 
	if (sphere->center().x <= sphereCase.X + (_grid.WidthCase() * _grid.Margin()))
	{
		CollisionGridCase left(sphereCase.X - 1, sphereCase.Y);
		_spheres[left].push_back(sphere);
		sphere->AddIndex(left, _spheres[left].size() - 1);
	}
	else if (sphere->center().x >= sphereCase.X + (_grid.WidthCase() * (1.0 - _grid.Margin())))
	{
		CollisionGridCase right(sphereCase.X + 1, sphereCase.Y);
		_spheres[right].push_back(sphere);
		sphere->AddIndex(right, _spheres[right].size() - 1);
	}
	if (sphere->center().y <= sphereCase.Y + (_grid.WidthCase() * _grid.Margin()))
	{
		CollisionGridCase bottom(sphereCase.X, sphereCase.Y - 1);
		_spheres[bottom].push_back(sphere);
		sphere->AddIndex(bottom, _spheres[bottom].size() - 1);
	}
	else if (sphere->center().y >= sphereCase.Y + (_grid.WidthCase() * (1.0 - _grid.Margin())))
	{
		CollisionGridCase top(sphereCase.X, sphereCase.Y + 1);
		_spheres[top].push_back(sphere);
		sphere->AddIndex(top, _spheres[top].size() - 1);
	}
}

void CollisionManager::DeleteSphere(const std::shared_ptr<BoundingSphere>& sphere)
{
	// Delete all references of the box in cases
	for (auto it = sphere->Indices().begin(); it != sphere->Indices().end(); ++it)
	{
		_spheres[it->first].erase(_spheres[it->first].begin() + it->second);
		updateCaseIndices(it->first, it->second);
	}
	sphere->Indices().clear();
}

void CollisionManager::updateCaseIndices(const CollisionGridCase& gridCase, int indexDeadSphere)
{
	for (size_t i = indexDeadSphere; i < _spheres[gridCase].size(); i++)
		_spheres[gridCase][i]->DecreaseIndexCase(gridCase);
}